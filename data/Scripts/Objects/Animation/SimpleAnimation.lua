Script.Speed=1.0--float
Script.Sequence=0--int

function Script:Draw()
self.entity:SetAnimationFrame(8,1,4)
	--local t = Time:GetCurrent()
	--self.entity:SetAnimationFrame(t/100.0*self.Speed,1,self.Sequence)
end
