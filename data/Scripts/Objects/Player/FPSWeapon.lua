import "Scripts/AnimationManager.lua"

Script.offset=Vec3(0,0,0)--Vec3 "Offset"
Script.clipsize=6--int "Clip size"
Script.ammo=200--int "Ammunition"
Script.maxswayamplitude=0.01
Script.amplitude=0
Script.swayspeed=0
Script.timeunits=0
Script.smoothedposition=Vec3(0)
Script.smoothedrotation=Vec3(0)
Script.verticalbob=0
Script.jumpoffset=0
Script.landoffset=0
Script.firetime=0
Script.bulletrange=1000
Script.bulletforce=500
Script.bulletdamage=10
Script.reloading=false
Script.clipammo=Script.clipsize
Script.dryfiresoundfile=""--path "Dry fire" "Wav File (*wav):wav|Sound"
Script.fire1soundfile=""--path "Fire sound 1" "Wav File (*wav):wav|Sound"
Script.fire2soundfile=""--path "Fire sound 2" "Wav File (*wav):wav|Sound"
Script.fire3soundfile=""--path "Fire sound 3" "Wav File (*wav):wav|Sound"
Script.ricochet1soundfile=Sound:Load("Sound/Ricochet/bullet_impact_dirt_01.wav")
Script.ricochet2soundfile=Sound:Load("Sound/Ricochet/bullet_impact_dirt_02.wav")
Script.ricochet3soundfile=Sound:Load("Sound/Ricochet/bullet_impact_dirt_03.wav")
Script.reloadsoundfile=""--path "Reload sound" "Wav File (*wav):wav|Sound"

function Script:Start()
	self.ammo = self.ammo - self.clipammo
	
	self.sound={}
	if self.sound.dryfiresoundfile~="" then self.sound.dryfire=Sound:Load(self.dryfiresoundfile) end
	self.sound.fire={}
	if self.sound.fire1soundfile~="" then self.sound.fire[0]=Sound:Load(self.fire1soundfile) end
	if self.sound.fire2soundfile~="" then self.sound.fire[1]=Sound:Load(self.fire2soundfile) end
	if self.sound.fire3soundfile~="" then self.sound.fire[2]=Sound:Load(self.fire3soundfile) end
	if self.reloadsoundfile~="" then
		self.sound.reload=Sound:Load(self.reloadsoundfile)
	end
	self.sound.ricochet={}
	self.sound.ricochet[0]=Sound:Load("Sound/Ricochet/bullet_impact_dirt_01.wav")
	self.sound.ricochet[1]=Sound:Load("Sound/Ricochet/bullet_impact_dirt_02.wav")
	self.sound.ricochet[2]=Sound:Load("Sound/Ricochet/bullet_impact_dirt_03.wav")
	
	self.entity:SetPickMode(0)
	
	self.muzzleflash = Model:Load("Models/Primitives/Plane.mdl")
	self.muzzleflash:SetCollisionType(0)
	local material = Material:Load("Materials/Effects/muzzleflash.mat")
	self.muzzleflash:SetMaterial(material)
	self.muzzleflash:SetScale(0.25)
	self.muzzlelight = PointLight:Create()
	self.muzzlelight:SetColor(1,0.75,0)
	self.muzzlelight:SetRange(4)
	self.muzzleflash:SetShadowMode(0)
	local tag = self.entity:FindChild("j_gun")
	self.muzzlelight:SetParent(tag)
	self.muzzlelight:SetPosition(0,0.2,0.5)
	self.muzzlelight:Hide()
	self.muzzleflash:SetParent(self.muzzlelight,false)
	self.animationmanager = AnimationManager:Create(self.entity)
	self.originalposition = self.entity:GetPosition()
	self.originalrotation = self.entity:GetRotation()
	self.emitter={}
	
	--Debris emitter - This will throw chunks off of walls and make it look like they are breaking
	self.emitter[0]=Emitter:Create()
	self.emitter[0]:SetMaterial("Materials/Effects/default.mat")
	self.emitter[0]:SetEmissionVolume(0.05,0.05,0.05)	
	self.emitter[0]:SetColor(0.1,0.1,0.1,1)
	self.emitter[0]:SetVelocity(1.5,1.5,1.5,1)
	self.emitter[0]:SetParticleCount(10)
	self.emitter[0]:SetReleaseQuantity(10)
	self.emitter[0]:SetMaxScale(0.3)
	self.emitter[0]:SetDuration(1000)
	self.emitter[0]:SetAcceleration(0,-12,0)
	self.emitter[0]:Hide()
	
	--Smoke emitter - This will provide a soft dust effect around bullet impacts
	self.emitter[1]=Emitter:Create()
	self.emitter[1]:SetColor(1,1,1,0.25)
	self.emitter[1]:SetMaterial("Materials/Effects/smoke.mat")
	self.emitter[1]:SetEmissionVolume(0.1,0.1,0.1)
	self.emitter[1]:SetVelocity(0.3,0.3,0.3,1)
	self.emitter[1]:SetParticleCount(3)
	self.emitter[1]:SetReleaseQuantity(3)
	self.emitter[1]:SetMaxScale(4)
	self.emitter[1]:SetDuration(2500)
	self.emitter[1]:AddScaleControlPoint(0,0.5)
	self.emitter[1]:AddScaleControlPoint(1,1)
	self.emitter[1]:SetRotationSpeed(10)
	self.emitter[1]:Hide()
	
	--Blood emitter - This will provide a visual cue when an enemy is shot
	self.emitter[2]=self.emitter[1]:Instance()
	self.emitter[2] = tolua.cast(self.emitter[2],"Emitter")
	self.emitter[2]:SetMaterial("Materials/Effects/bloodspatter.mat")
	self.emitter[2]:SetColor(1,1,1,0.25)
	self.emitter[2]:SetParticleCount(3)
	self.emitter[2]:SetReleaseQuantity(3)
	self.emitter[2]:SetDuration(200)
	self.emitter[2]:SetEmissionVolume(0,0,0)
	self.emitter[2]:SetMaxScale(1)
	self.emitter[2]:SetRotationSpeed(10)
	self.emitter[2]:AddScaleControlPoint(0,0)
	self.emitter[2]:AddScaleControlPoint(1,1)
	self.emitter[2]:SetVelocity(0,0,0,0)
	self.emitter[2]:SetVelocity(0,0,0,1)
	self.emitter[2]:Hide()
end

function Script:Hide()
	self.entity:Hide()
	self.muzzleflash:Hide()
	self.muzzlelight:Hide()
end

function Script:FindScriptedParent(entity,func)
	while entity~=nil do
		if entity.script then
			if type(entity.script[func])=="function" then
				if entity.script.enabled~=false then
					return entity
				else
					return nil
				end
			end
		end
		entity = entity:GetParent()
	end
	return nil
end

function Script:BeginJump()
	self.jumpoffset = -180
end

function Script:BeginLand()
	self.landoffset = -180
end

function Script:EndReload()
	self.reloading=false
	local rounds = self.clipsize - self.clipammo
	rounds = math.min(self.ammo,rounds)
	self.ammo = self.ammo - rounds
	self.clipammo = self.clipammo + rounds	
end

function Script:Reload()
	if self.clipammo<self.clipsize and self.ammo>0 and self.reloading~=true then
		self.reloading=true
		self.animationmanager:SetAnimationSequence(0,0.02,300,1,self,self.EndReload,25)
		self.reloadstarttime=Time:GetCurrent()
		if self.sound.reload~=nil then self.sound.reload:Play() end
	end
end

function Script:Fire()
	if self.reloading==false then
		if self.clipammo==0 then
			self.sound.dryfire:Play()
		else		
			self.sound.fire[math.random(#self.sound.fire)]:Play()
			
			self.clipammo = self.clipammo - 1

			self.firetime = Time:GetCurrent()
			self.muzzlelight:Point(self.player.camera,1)
			self.muzzlelight:Turn(0,math.random(0,360),0)
			self.muzzlelight:Show()
			self.animationmanager:SetAnimationSequence(2,0.08,300,1)
			
			local d = Transform:Normal(0,0,1,self.entity,nil)
			local p = self.player.camera:GetPosition(true)
			local pickinfo=PickInfo()
			if self.entity.world:Pick(p,p+d*self.bulletrange,pickinfo,0,true,Collision.Prop) then
				
				--Find first parent with the Hurt() function
				local enemy = self:FindScriptedParent(pickinfo.entity,"Hurt")
				if enemy~=nil then
					if enemy.script.health>0 then
						enemy.script:Hurt(self.bulletdamage,self.player)
					end
					
					--Blood emitter
					e = self.emitter[2]:Instance()
					e = tolua.cast(e,"Emitter")
					e:Show()
					e:SetLoopMode(false,true)
					e:SetPosition(pickinfo.position+pickinfo.normal*0.1)
					e:SetVelocity(0,0,0)
					
				else
					
					--Add a temporary particle emitter for bullet effects
					local e
					
					e = self.emitter[0]:Instance()
					e = tolua.cast(e,"Emitter")
					e:Show()
					e:SetLoopMode(false,true)
					e:SetPosition(pickinfo.position)
					local v=3
					e:SetVelocity(pickinfo.normal.x*v,pickinfo.normal.y*v,pickinfo.normal.z*v,0)
					
					--Smoke emitter
					e = self.emitter[1]:Instance()
					e = tolua.cast(e,"Emitter")
					e:Show()
					e:SetLoopMode(false,true)
					e:SetPosition(pickinfo.position+pickinfo.normal*0.1)
					local v=0.2
					e:SetVelocity(pickinfo.normal.x*v,pickinfo.normal.y*v,pickinfo.normal.z*v,0)
					
					--Play bullet impact noise
					e:EmitSound(self.sound.ricochet[math.random(#self.sound.ricochet)])

					if pickinfo.entity~=nil then
						
						--Add impulse to the hit object
						if pickinfo.entity:GetMass()>0 then
							--local force = pickinfo.normal*-1*self.bulletforce
							local force = d * self.bulletforce * math.max(0,-pickinfo.normal:Dot(d))
							--force = force * math.max(0,-pickinfo.normal:Dot(d))--multiply by dot product of velocity and collided normal, to weaken glancing blows
							pickinfo.entity:AddPointForce(force,pickinfo.position)
						end
						
						--Extract a partial surface from the hit surface and make a bullet mark
						--To be added later
						if pickinfo.surface~=nil then
							--local aabb = AABB(pickinfo.position-radius,pickinfo.position+radius)	
							--local surf = pickinfo.surface:Extract(aabb)
						end
					end
				end
			end
		end
	end
end

function Script:Draw()
	local t = Time:GetCurrent()

	if self.muzzlelight:Hidden()==false then
		if t-self.firetime>50 then
			self.muzzlelight:Hide()
		end
	end
	
	local jumpbob = 0
	
	if self.jumpoffset<0 then
		jumpbob = (Math:Sin(self.jumpoffset))*0.01
		self.jumpoffset = self.jumpoffset + 8
	end
	
	if self.landoffset<0 then
		jumpbob = jumpbob + (Math:Sin(self.landoffset))*0.01
		self.landoffset = self.landoffset + 10
	end

	--Animate the weapon
	local bob = 0;
	local speed = math.max(0.1,self.player.entity:GetVelocity():xz():Length())
	if self.player.entity:GetAirborne() then speed = 0.1 end
	self.swayspeed = Math:Curve(speed,self.swayspeed,20)
	self.swayspeed = math.max(0.5,self.swayspeed)
	self.amplitude = math.max(2,Math:Curve(speed,self.amplitude,20))
	self.timeunits = self.timeunits + self.swayspeed*4*Time:GetSpeed()
	local sway = math.sin(self.timeunits/120.0) * self.amplitude * self.maxswayamplitude
	bob = (1-math.cos(self.timeunits/60.0)) * self.maxswayamplitude * 0.1 * self.amplitude
	local campos = self.player.camera:GetPosition(true)
	
	self.smoothedposition.x = campos.x
	self.smoothedposition.y = Math:Curve(campos.y,self.smoothedposition.y,2)
	self.smoothedposition.z = campos.z
	
	self.entity:LockMatrix()
	self.entity:SetPosition(sway*self.entity.scale.x,bob+jumpbob,0)
	self.entity:Translate(self.offset.x,self.offset.y,self.offset.z)
	self.animationmanager:Update()
	self.entity:UnlockMatrix()
end

function Script:Release()
	self.emitter[0]:Release()
	self.emitter[1]:Release()
	self.emitter=nil
end
