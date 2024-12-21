# PointLight3D

A node that emits light from a single point. Light intensity will attenuate as distance from the node increases.

---
### SetRadius
Set the light radius. Beyond the radius, light intensity will be zero.

Sig: `PointLight3D:SetRadius(radius)`
 - Arg: `number radius` Light radius
---
### GetRadius
Get the light radius. Beyond the radius, light intensity will be zero.

Sig: `radius = PointLight3D:GetRadius()`
 - Ret: `number radius` Light radius
---