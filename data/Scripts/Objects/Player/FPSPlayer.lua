import "Scripts/Functions/ReleaseTableObjects.lua"

Script.health = 100		--float "Health"
Script.maxHealth = 100		--float "Max Health"
Script.mouseSensitivity = 15 	--float "Mouse sensitivity"
Script.camSmoothing = 	2 	--float "Cam smoothing" 
Script.moveSpeed = 2.5 		--float "Move Speed"
Script.speedMultiplier = 1.5 	--float "Run Multiplier"
Script.strafeSpeed = 4 		--float "Strafe Speed"
Script.playerHeight = 1.8 	--float "Player Height"
Script.jumpForce = 8 		--float "Jump Force"
Script.flashlighton = false	--bool "Flashlight on"
Script.useDistance = 2
Script.alive=true
Script.eyeheight=1.6
Script.footstepwalkdelay = 500
Script.footsteprundelay = 300
Script.weaponfile=""--path "Weapon" "Prefab (*.pfb):pfb|Prefabs"
Script.input={}
Script.maxcarryweight=5
Script.throwforce = 500
Script.isairborne=false
Script.bloodindex=1
Script.teamid=1--choice "Team" "Neutral,Good,Bad"
Script.hurtoffset=Vec3(0)
Script.smoothedhurtoffset=Vec3(0)
Script.mouseDifference = Vec2(0,0)
Script.playerMovement = Vec3(0,0,0)
Script.tempJumpForce = 0

--This function will be called when an entity is loaded in a map.  Use this for intitial setup stuff.
function Script:Start()
	self.camRotation = self.entity:GetRotation(true)
	
	self.image={}
	self.image.crosshair = Texture:Load("Materials/HUD/crosshair.tex")
	self.image.hand = Texture:Load("Materials/HUD/use.tex")
	
	self.image.blood={}
	self.image.blood[1]=Texture:Load("Materials/HUD/blood1.tex")
	self.image.blood[2]=Texture:Load("Materials/HUD/blood2.tex")
	self.image.blood[3]=Texture:Load("Materials/HUD/blood3.tex")
	self.image.blood[4]=Texture:Load("Materials/HUD/blood4.tex")
	
	--Load shared sounds
	self.sound={}--table to store sound in
	self.sound.flashlight=Sound:Load("Sound/Player/flashlight_02_on.wav")
	self.sound.damage={}
	self.sound.damage[1]=Sound:Load("Sound/Impact/body_punch_03.wav")
	self.sound.damage[2]=Sound:Load("Sound/Impact/body_punch_04.wav")
	self.sound.footsteps={}
	self.sound.footsteps.concrete={}
	self.sound.footsteps.concrete.step={}
	local n
	for n=1,4 do
		self.sound.footsteps.concrete.step[n] = Sound:Load("Sound/Footsteps/Concrete/step"..tostring(n)..".wav")
	end
	self.sound.footsteps.concrete.jump = Sound:Load("Sound/Footsteps/Concrete/jump.wav")
	
	self.bloodoverlay={}

	self.entity:SetPickMode(0)
	
	--Set the type for this object to player
	self.entity:SetKeyValue("type","player")
	
	local mass = self.entity:GetMass()
	if self.entity:GetMass()==0 then Debug:Error("Player mass should be greater than 0.") end

	--Create a camera
	self.camera = Camera:Create()
	self.camera:SetMultisampleMode((System:GetProperty("multisample","1")))
		
	--Set the camera's rotation to match the player
	self.camera:SetRotation(self.entity:GetRotation(true))
	
	--Set the camera position at eye height
	self.camera:SetPosition(self.entity:GetPosition(true)+Vec3(0,self.eyeheight,0))
	
	self.listener = Listener:Create(self.camera)	
	
	self.flashlight = SpotLight:Create()
	self.flashlight:SetParent(self.camera,false)
	self.flashlight:SetPosition(0.2,-0.1,0)
	self.flashlight:SetRotation(10,-3,0)
	self.flashlight:SetConeAngles(25,15)
	self.flashlight:SetShadowMode(Light.Dynamic+Light.Static)
	if self.flashlighton==false then
		self.flashlight:Hide()
	end
	
	--Load the default weapon, if one is set
	if self.weaponfile~="" then
		local entity = Prefab:Load(self.weaponfile)
		if entity~=nil then
			if entity.script~=nil then
				entity.script.player = self
				self.weapon = entity.script
				self.weapon.entity:SetParent(self.camera)
				self.weapon.entity:SetRotation(0,0,0)
				if self.weapon.offset~=nil then
					self.weapon.entity:SetPosition(self.weapon.offset)
				else
					self.weapon.entity:SetPosition(0,0,0)
				end
			end
		end
	end
	
	---------------------------------------------------------------------------
	--We want the player model visible in the editor, but invisible in the game
	--We can achieve this by creating a material, setting the blend mode to make
	--it invisible, and applying it to the model.
	---------------------------------------------------------------------------
	local material = Material:Create()
	material:SetBlendMode(5)--Blend.Invisible
	self.entity:SetMaterial(material)
	material:Release()
	self.entity:SetShadowMode(0)
	
	local window = Window:GetCurrent()
	local context = Context:GetCurrent()
	window:SetMousePosition(Math:Round(context:GetWidth()/2), Math:Round(context:GetHeight()/2))
	
	self.camera:SetRotation(self.camRotation)
end

function Script:Release()
	self.listener:Release()
	self.flashlight:Release()
	if self.corpse~=nil then
		self.corpse:Release()
		self.corpse=nil
	end
	ReleaseTableObjects(self.sound)
	ReleaseTableObjects(self.image)
end

function Script:Collision(entity,position,normal,speed)
	if speed>20 then
		self:Hurt(100)
	end
end

function Script:Hurt(damage,distributorOfPain)
	if self.health>0 then
		self.sound.damage[math.random(#self.sound.damage)]:Play()
		self.health = self.health - damage
		self.hurtoffset = Vec3(math.random(-1,1),math.random(-1,1),0):Normalize()*30
		local blood = {}
		local n=1
		blood.texture=self.image.blood[math.random(1,4)]
		blood.intensity=1
		table.insert(self.bloodoverlay,blood)		
		if self.bloodindex>4 then self.bloodindex=1 end
		if self.health<=0 then
			self:Kill()
		end
	end
end

function Script:Kill()
	self.corpse = Pivot:Create()
	local shape = Shape:Load("Models/Characters/Generic/corpse.phy")--this shape is made from a low-poly CSG sphere, so it will roll around a bit but come to a stop quickly
	self.corpse:SetShape(shape)
	if shape~=nil then shape:Release() end
	self.flashlight:Hide()
	if self.weapon~=nil then
		self.weapon:Hide()
	end
	self.corpse:SetMass(5)
	self.corpse:SetMatrix(self.camera:GetMatrix())
	self.camera:SetParent(self.corpse)
	self.camera:SetPosition(0,0,0)
	self.camera:SetRotation(0,0,0)
	self.corpse:SetCollisionType(Collision.Prop)
	self.corpse:SetSweptCollisionMode(true)
	self.entity:SetCollisionType(0)
	self.corpse:SetFriction(10,10)
	local maxomega=5
	self.corpse:SetOmega(Vec3(math.random(-maxomega,maxomega),math.random(-maxomega,maxomega),math.random(-maxomega,maxomega)))
	local v = self.entity:GetVelocity()
	if v:Length()>1 then
		v=v:Normalize()
	end
	self.corpse:SetVelocity(Vec3(math.random(-1,1),math.random(-1,1),math.random(-1,1)))
	self.entity:SetMass(0)
	self.entity:SetPhysicsMode(Entity.RigidBodyPhysics)
end

function Script:FindUsableEntity(entity)
	while entity~=nil do
		if entity.script then
			if type(entity.script.Use)=="function" then
				--If "enable" has not been set, it still won't be "false" so this will pass:
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

function Script:UpdateWorld()

	--Exit the function early if the player is dead
	if self.health<=0 then return end
	
	local window = Window:GetCurrent()
	local context=Context:GetCurrent()
	
	if window:KeyHit(Key.P) then
		self.camera:SetDebugPhysicsMode(true)
	end
	
	if self.isairborne==true then
		if self.entity:GetAirborne()==false then
			if self.weapon~=nil then
				self.weapon:BeginLand()
			end
		end
	end
	self.isairborne = self.entity:GetAirborne()
	
	--Mouse look
	self.currentMousePos = window:GetMousePosition()
	window:SetMousePosition(Math:Round(context:GetWidth()/2), Math:Round(context:GetHeight()/2))
	self.currentMousePos.x = Math:Round(self.currentMousePos.x)
	self.currentMousePos.y = Math:Round(self.currentMousePos.y)


--System:Print(self.currentMousePos.y)
--System:Print(Math:Round(context:GetHeight())/2)

	self.mouseDifference.x = Math:Curve(self.currentMousePos.x - Math:Round(context:GetWidth()/2),self.mouseDifference.x,3)
	self.mouseDifference.y = Math:Curve(self.currentMousePos.y - Math:Round(context:GetHeight()/2),self.mouseDifference.y,3)
	self.camRotation.x = Math:Clamp(self.camRotation.x + self.mouseDifference.y / self.mouseSensitivity,-90,90)
	self.camRotation.y = self.camRotation.y + (self.mouseDifference.x / self.mouseSensitivity)
	
	--Adjust the view shake
	self.hurtoffset.x = Math:Inc(0,self.hurtoffset.x,2*Time:GetSpeed())
	self.hurtoffset.y = Math:Inc(0,self.hurtoffset.y,2*Time:GetSpeed())
	self.smoothedhurtoffset.x = Math:Curve(self.hurtoffset.x,self.smoothedhurtoffset.x,3)
	self.smoothedhurtoffset.y = Math:Curve(self.hurtoffset.y,self.smoothedhurtoffset.y,3)
	
	--Set the camera angle
	self.camera:SetRotation(self.camRotation+self.smoothedhurtoffset)
	
	--Picking and usage 
	local pickInfo = PickInfo()
	
	--Raycast Pick that is being send from the camera in to the world
	self.canUse = false
	
	if window:MouseHit(1) then
		if self.carryingEntity then
			local dir = Transform:Vector(0,0,self.throwforce,self.camera,nil)
			self.carryingEntity:AddForce(dir)
			self:DropEntityCarrying()
		else
			if self.weapon~=nil then
				self.weapon:Fire()
			end
		end
	end
	
	if self.weapon~=nil then
		if window:KeyHit(Key.R) then
			self.weapon:Reload()
		end
	end
	
	if window:KeyHit(Key.E) then
		if self.carryingEntity then
			self:DropEntityCarrying()
		else
			local p0 = self.camera:GetPosition(true)
			local p1 = Transform:Point(0,0,self.useDistance,self.camera,nil)
			if self.entity.world:Pick(p0,p1, pickInfo, 0, true) then 
				
				--Looks for any entity in the hierarchy that has a "Use" function
				local usableentity = self:FindUsableEntity(pickInfo.entity)
				
				if usableentity~=nil then
					
					--Use the object, whatever it may be
					usableentity.script:Use()
				
				elseif self.carryingEntity == nil then
					mass = pickInfo.entity:GetMass()
					
					--Pick up object if it isn't too heavy
					if mass>0 and mass<=self.maxcarryweight then
						self.carryingEntity = pickInfo.entity
						self.carryingobjectcollisiontype = self.carryingEntity:GetCollisionType()
						self.carryingEntity:SetCollisionType(Collision.Debris)
						self.carryrotation = Transform:Rotation(pickInfo.entity:GetQuaternion(true),nil,self.camera)
						self.carryposition = Transform:Point(pickInfo.entity:GetPosition(true),nil,self.camera)
					end
				end
			end
		end
	end
	
	--The icon that shows that an object can be picked up or can be interacted with
	--Amnesia fan, I see. :D
	if self.carryingEntity == nil then
		local p0 = self.camera:GetPosition(true)
		local p1 = Transform:Point(0,0,self.useDistance,self.camera,nil)
		if self.entity.world:Pick(p0,p1, pickInfo, 0, true) then 
			if self:FindUsableEntity(pickInfo.entity)~=nil then
				self.canUse=true
			else
				local mass = pickInfo.entity:GetMass()
				if mass>0 and mass<=self.maxcarryweight then
					self.canUse = true
				end
			end
		end
	end
end

function Script:DropEntityCarrying()
	self.carryingEntity:SetCollisionType(self.carryingobjectcollisiontype)
	self.carryingEntity = nil
end

--This function plays footstep sounds in regular intervals as the player walks
function Script:UpdateFootsteps() 
	if self.lastfootsteptime==nil then self.lastfootsteptime=0 end
	if self.input[0]~=0 or self.input[1]~=0 then
		local speed = self.entity:GetVelocity():xz():Length()
		if self.entity:GetAirborne()==false then
			if (speed>self.moveSpeed*0.5) then
				local t = Time:GetCurrent()
				local repeatdelay = self.footstepwalkdelay
				if speed>self.moveSpeed * (1+(self.speedMultiplier-1)*0.5) then repeatdelay = self.footsteprundelay end
				if t-self.lastfootsteptime>repeatdelay then
					self.lastfootsteptime = t
					local index = math.random(1,4)
					self.sound.footsteps.concrete.step[index]:Play()
				end
			end
		end
	end
end

--This function will be called once per physics update
function Script:UpdatePhysics()
	
	--Exit the function early if the player is dead
	if self.health<=0 then return end
	
	local window = Window:GetCurrent()
	
	--Fade out the screen blood
	if self.bloodintensity~=nil then
		if self.bloodintensity>0 then
			self.bloodintensity = self.bloodintensity-0.01
			self.bloodintensity = math.max(0,self.bloodintensity)
		end
	end
	
	--Update the footstep sounds when walking
	self:UpdateFootsteps()

	--Toggle the flash light on and off
	if window:KeyHit(Key.F) then
		self.sound.flashlight:Play()
		if self.flashlight:Hidden() then
			self.flashlight:Show()
		else
			self.flashlight:Hide()
		end
	end

	--Apply forces to make the carried object move the way we want
	if self.carryingEntity then
		local currentpos = self.carryingEntity:GetPosition(true)
		
		local pos = Transform:Point(self.carryposition,self.camera,nil)
		local rot = Transform:Rotation(self.carryrotation,self.camera,nil)
		
		local maxdiff = 0.5
		local diff = pos:DistanceToPoint(currentpos)
		
		--Drop the carryinItem when the distance between camera and item exceed the pickdistance
		if diff>1.5 then
			self:DropEntityCarrying()
		else
			if diff>maxdiff then
				pos = currentpos + (pos-currentpos):Normalize()*maxdiff
				diff = maxdiff
			end			
			self.carryingEntity:PhysicsSetPosition(pos.x,pos.y,pos.z,0.25)
			self.carryingEntity:PhysicsSetRotation(rot,0.5)
		end
	end
	
	--only update camera and movement when the player is alive

--[[
	--Get the mouse movement
	currentMousePos = App.window:GetMousePosition()
	mouseDifference.x = currentMousePos.x - centerMouse.x
	mouseDifference.y = currentMousePos.y - centerMouse.y

	--Adjust and set the camera rotation with regard to maximum and minimum look angles
	if (math.abs(mouseDifference.x)) > 0.01 and (math.abs(mouseDifference.y)) > 0.01 then
		camRotation.x = camRotation.x + (mouseDifference.y / mouseSensitivity)
		camRotation.x = Math:Clamp(camRotation.x,-90,90)
		camRotation.y = camRotation.y + (mouseDifference.x / mouseSensitivity)
		self.camera:SetRotation(camRotation)
	end
	App.window:SetMousePosition(centerMouse.x, centerMouse.y)
]]--
	--Player Movement
	local movex=0
	local movez=0
	self.input[0]=0
	self.input[1]=0
	if window:KeyDown(Key.W) then self.input[1]=self.input[1]+1 end
	if window:KeyDown(Key.S) then self.input[1]=self.input[1]-1 end
	if window:KeyDown(Key.D) then self.input[0]=self.input[0]+1 end
	if window:KeyDown(Key.A) then self.input[0]=self.input[0]-1 end
	
	local playerMovement = Vec3(0)
	playerMovement.x = self.input[0] * self.moveSpeed
	playerMovement.z = self.input[1] * self.moveSpeed
	
	--This prevents "speed hack" strafing due to lazy programming
	if self.input[0]~=0 and self.input[1]~=0 then
		playerMovement = playerMovement * 0.70710678
	end

	--if self.entity:GetAirborne() then
	--	playerMovement = playerMovement * 0.2
	--end
	
	--Check for running with shift and when not carrying anything
	if self.carryingEntity == nil and window:KeyDown(Key.Shift) then
		playerMovement.z = playerMovement.z  * self.speedMultiplier
	end

	-- Check for jumping
	local jump = 0
	if window:KeyHit(Key.Space) and self:IsAirborne() == 0 then
		jump = self.jumpForce
		
		self.sound.footsteps.concrete.jump:Play()

		if self.weapon~=nil then
			self.weapon:BeginJump()
		end

		--Give the player an extra boost when jumping
		playerMovement = playerMovement * 1.6
	end
	
	-- Check for crouching
	--if App.window:KeyHit(Key.ControlKey) then
	--	crouched = not crouched
	--end
	
	--With smoothing 
	--Position camera at correct height and playerPosition
	self.entity:SetInput(self.camRotation.y, playerMovement.z, playerMovement.x, jump , false, 1.0, 0.5, true)
	local playerPos = self.entity:GetPosition()
	local newCameraPos = self.camera:GetPosition()
	--local playerTempHeight = ((self:IsCrouched() == 1) and crouchHeight or playerHeight)
	newCameraPos = Vec3(playerPos.x, newCameraPos.y ,playerPos.z)
	
	if newCameraPos.y<playerPos.y + self.eyeheight then
		newCameraPos.y = Math:Curve(playerPos.y + self.eyeheight, newCameraPos.y, self.camSmoothing)
	else
		newCameraPos.y = playerPos.y + self.eyeheight
	end
	
	self.camera:SetPosition(newCameraPos)

end

--Return whether the player is airborne
function Script:IsAirborne()
	return self.entity:GetAirborne() and 1 or 0
end

function Script:PostRender(context)
	context:SetBlendMode(Blend.Alpha)
	
	-----------------------------------------------------------------------
	--Draw the blood overlay on the screen to indicate damage
	local k,v
	for k,v in pairs(self.bloodoverlay) do
		if v.intensity>0 then
			context:SetColor(1,1,1,v.intensity*0.5)
			context:DrawImage(v.texture,0,0,context:GetWidth(),context:GetHeight())
			if self.health>0 then
				v.intensity = v.intensity-0.02 * Time:GetSpeed()
			end
		else
			self.bloodoverlay[k]=nil
		end
	end
	context:SetColor(1,1,1,1)
	
	if self.health>0 then
		if self.canUse==true and self.carryingEntity == nil then
			local pickUpX = math.floor((context:GetWidth() - self.image.hand:GetWidth()))/2
			local pickUpY = math.floor((context:GetHeight() - self.image.hand:GetHeight()))/2
			context:SetBlendMode(Blend.Alpha)
			context:DrawImage(self.image.hand, pickUpX, pickUpY)	
		else
			if self.carryingEntity==nil then
				if self.weapon~=nil then
					if self.image.crosshair then
						local crossHairX = math.floor((context:GetWidth() - self.image.crosshair:GetWidth()))/2
						local crossHairY = math.floor((context:GetHeight() - self.image.crosshair:GetHeight()))/2
						context:SetBlendMode(Blend.Alpha)
						context:DrawImage(self.image.crosshair, crossHairX, crossHairY)
					end
				end
			end
		end
	end
	
	context:SetBlendMode(1)
	context:SetColor(0,0,0,0.5)
	local indent=8
	local w = 180
	local h = 40
end

--Return whether the player is crouching
function Script:IsAlive()
	return self.alive and 1 or 0
end

--TakeDamage
function Script:TakeDamage(damage)

	--Decrease health
	self.health = self.health - damage;

	--Call OnHit output
	self:OnHit()

	--If health lower or equal to zero, the player is dead
	if self.health <= 0 then
		self.alive = false
		--Call the OnDead output
		self:OnDead()
	end
end

--Increase health
function Script:ReceiveHealth(healthPoints)--in
	--Increase health
	self.health = self.health + healthPoints;

	--Health can not be more then maximum health
	if self.health > self.maxHealth then
		self.health = self.maxHealth
	end
	
	--Call Health received output
	self.component:CallOutputs("HealthReceived")
end

--when health is zero or lower, an output call is made
function Script:OnDead()--out
	--Extra check to make sure that the player is no longer alive
	if not(self:IsAlive()) then
		self.component:CallOutputs("Ondead")
	end
end

--when the player gets damaged we call this output
function Script:OnHit()--out
	self.component:CallOutputs("OnHit")
end
