import "Scripts/AnimationManager.lua"
import "Scripts/Functions/GetEntityNeighbors.lua"

--Public values
Script.health=40--int "Health"
Script.enabled=true--bool "Enabled"
Script.target=nil--entity "Target"
Script.sightradius=30--float "Sight Range"
Script.senseradius=2--float "Hearing Range"
Script.teamid=2--choice "Team" "Neutral,Good,Bad"

--Private values
Script.damage=5
Script.attackrange=1.5
Script.updatefrequency=500
Script.lastupdatetime=0
Script.prevtarget=nil
Script.animation={}
Script.animation.idle=0
Script.animation.run=1
Script.animation.attack={}
Script.animation.attack[0]=4
Script.animation.attack[1]=2
Script.animation.death=3
Script.followingtarget=false
Script.maxaccel=10
Script.speed=6
Script.lastupdatetargettime=0
Script.attackmode=0
Script.attackbegan=0
Script.sound={}
Script.sound.alert = Sound:Load("Sound/Characters/mutant_injure_02.wav")
Script.sound.attack={}
Script.sound.attack[1] = Sound:Load("Sound/Characters/mutant_attack_04.wav")
Script.sound.attack[2] = Sound:Load("Sound/Characters/mutant_attack_06.wav")

function Script:Enable()--in
	if self.enabled==false then
		if self.health>0 then
			self.enabled=true
			if self.target~=nil then
				self:SetMode("roam")
			else
				self:SetMode("idle")
			end
		end
	end
end

function Script:ChooseTarget()
	local entities = GetEntityNeighbors(self.entity,self.sightradius,true)
	local k,entity
	for k,entity in pairs(entities) do
		if entity.script.teamid~=nil and entity.script.teamid~=0 and entity.script.teamid~=self.teamid then
			if entity.script.health>0 then
				local d = self.entity:GetDistance(entity)
				--if d<self.senseradius then
				--	return entity.script
				--else
				--	local p = Transform:Point(entity:GetPosition(),nil,self.entity)
				--	if (p.z>-math.abs(p.x) and p.z<-math.abs(p.y)) then
						local pickinfo=PickInfo()
						if self.entity.world:Pick(self.entity:GetPosition()+Vec3(0,1.6,0),entity:GetPosition()+Vec3(0,1.6,0),pickinfo,0,false,Collision.LineOfSight)==false then
							return entity.script
						end
				--	end
				--end
			end
		end
	end
end

function Script:DistanceToTarget()
	local pos = self.entity:GetPosition()
	local targetpos = self.target.entity:GetPosition()
	if math.abs(targetpos.y-pos.y)<1.5 then
		return pos:xz():DistanceToPoint(targetpos:xz())
	else
		return 100000--if they are on different vertical levels, assume they can't be reached
	end
end

function Script:TargetInRange()
	local pos = self.entity:GetPosition()
	local targetpos = self.target.entity:GetPosition()
	if math.abs(targetpos.y-pos.y)<1.5 then
		if pos:xz():DistanceToPoint(targetpos:xz())<self.attackrange then
			return true
		end
	end
	return false
end

--[[
function WorldGetEntitiesInAABBDoCallback(entity,extra)
	if entity~=extra then
		if GetEntityNeighborsScriptedOnly==false or entity.script~=nil then
			table.insert(WorldGetEntitiesInAABBDoCallbackTable,entity)
		end
	end
end

function GetEntityNeighbors(entity,radius,scriptOnly)
	local result
	local aabb = AABB()
	local p = entity:GetPosition(true)
	local temp = GetEntityNeighborsScriptedOnly
	GetEntityNeighborsScriptedOnly=scriptOnly
	aabb.min = p - radius
	aabb.max = p + radius
	aabb:Update()
	local table = WorldGetEntitiesInAABBDoCallbackTable 
	WorldGetEntitiesInAABBDoCallbackTable = {}
	entity.world:ForEachEntityInAABBDo(aabb,"WorldGetEntitiesInAABBDoCallback",entity)	
	result = WorldGetEntitiesInAABBDoCallbackTable
	WorldGetEntitiesInAABBDoCallbackTable = table
	GetEntityNeighborsScriptedOnly = temp
	return result
end
]]--

function Script:Start()
	self.animationmanager = AnimationManager:Create(self.entity)
	if self.enabled then
		if self.target~=nil then
			self:SetMode("roam")
		else
			self:SetMode("idle")
		end
	end
end

function Script:Hurt(damage,distributorOfPain)
	if self.health>0 then
		if self.target==nil then
			self.target=distributorOfPain
			self:SetMode("attack")
		end
		self.health = self.health - damage
		if self.health<=0 then
			self.entity:SetMass(0)
			self.entity:SetCollisionType(0)
			self.entity:SetPhysicsMode(Entity.RigidBodyPhysics)
			self:SetMode("dying")
		end
	end
end

function Script:EndDeath()
	self:SetMode("dead")
end

function Script:DirectMoveToTarget()
	self.entity:Stop()
	local targetpos = self.target.entity:GetPosition()
	local pos = self.entity:GetPosition()
	local dir = Vec2(targetpos.z-pos.z,targetpos.x-pos.x):Normalize()
	local angle = -Math:ATan2(dir.y,-dir.x)
	self.entity:SetInput(angle,self.speed)
end

function Script:SetMode(mode)
	if mode~=self.mode then
		local prevmode=self.mode
		self.mode=mode
		if mode=="idle" then
			self.target=nil
			self.animationmanager:SetAnimationSequence(0,0.02)
			self.entity:Stop()--stop following anything
		elseif mode=="roam" then
			if self.target~=nil then
				self.animationmanager:SetAnimationSequence(1,0.04)
				self.entity:GoToPoint(self.target:GetPosition(true),5,5)
			else
				self:SetMode("idle")
			end
		elseif mode=="attack" then
			self:EndAttack()
		elseif mode=="chase" then
			if self.entity:Follow(self.target.entity,self.speed,self.maxaccel) then
				if prevmode~="chase" then
					self.entity:EmitSound(self.sound.alert)
				end
				self.followingtarget=true
				self.animationmanager:SetAnimationSequence(self.animation.run,0.05,300)
				if self:DistanceToTarget()<self.attackrange*2 then
					self.followingtarget=false
					self.entity:Stop()
					self:DirectMoveToTarget()
				end
			else
				self.target=nil
				self:SetMode("idle")
				return
			end
		elseif mode=="dying" then
			self.entity:Stop()
			self.animationmanager:SetAnimationSequence(self.animation.death,0.04,300,1,self,self.EndDeath)			
		elseif mode=="dead" then
			self.entity:SetCollisionType(0)
			self.entity:SetMass(0)
			self.entity:SetShape(nil)
			self.entity:SetPhysicsMode(Entity.RigidBodyPhysics)
			self.enabled=false
		end
	end
end

function Script:EndAttack()
	if self.mode=="attack" then	
		if self.target.health<=0 then
			self:SetMode("idle")
			return
		end
		local d = self:DistanceToTarget()
		if d>self.attackrange then
			--if d>self.attackrange*2 then
				self:SetMode("chase")
				return
			--else
			--	local pos = self.entity:GetPosition()
			--	local targetpos = self.target.entity:GetPosition()
			--	self.entity:SetInput(-Math:ATan2(targetpos.x-pos.x,targetpos.y-pos.y),self.speed)
			--	return
			--end
		end
		self.entity:Stop()
		self.attackmode = 1-self.attackmode--switch between right and left attack modes	
		self.animationmanager:SetAnimationSequence(self.animation.attack[self.attackmode],0.04*math.random(1,1.25),300,1,self,self.EndAttack)
		self.attackbegan = Time:GetCurrent()
		if math.random()>0.75 then self.entity:EmitSound(self.sound.attack[self.attackmode+1]) end
	end
end

function Script:UpdatePhysics()
	if self.enabled==false then return end

	local t = Time:GetCurrent()
	self.entity:SetInput(self.entity:GetRotation().y,0)
	
	if self.mode=="idle" then
		if t-self.lastupdatetargettime>250 then
			self.lastupdatetargettime=t
			self.target = self:ChooseTarget()
			if self.target then
				self:SetMode("chase")
			end
		end
	elseif self.mode=="roam" then
		if self.entity:GetDistance(self.target)<1 then
			self:SetMode("idle")
		end
	elseif self.mode=="chase" then
		if self.target.health<=0 then
			self:SetMode("idle")
			return
		end
		if self:TargetInRange() then
			self:SetMode("attack")
		elseif self:DistanceToTarget()<self.attackrange*2 then
			self.followingtarget=false
			self.entity:Stop()
			self:DirectMoveToTarget()
		else
			if self.followingtarget==false then
				if self.entity:Follow(self.target.entity,self.speed,self.maxaccel) then
					self:SetMode("idle")
				end
			end
		end
	elseif self.mode=="attack" then
		if self.attackbegan~=nil then
			if t-self.attackbegan>300 then
				self.attackbegan=nil
				self.target:Hurt(self.damage)
			end
		end
		local pos = self.entity:GetPosition()
		local targetpos = self.target.entity:GetPosition()
		local dx=targetpos.x-pos.x
		local dz=targetpos.z-pos.z
		self.entity:AlignToVector(-dx,0,-dz)
	end
end

function Script:Draw()
	if self.enabled==false then return end
	self.animationmanager:Update()
end
