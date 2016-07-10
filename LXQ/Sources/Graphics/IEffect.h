#pragma once

#include <string>
#include "Uncopyable.h"


class IDevice;
class ID3D11Device;
class ID3D11DeviceContext;

class ID3DX11Effect;
class ID3DX11EffectTechnique;

class ID3DX11EffectVariable;
class ID3DX11EffectMatrixVariable;
class ID3DX11EffectScalarVariable;
class ID3DX11EffectShaderResourceVariable;


class IEffect : public Uncopyable
{
public:
	IEffect();
	~IEffect();

	virtual void Apply(ID3D11DeviceContext* context) = 0;

	ID3DX11EffectTechnique* GetTechnique(const std::string& name);

protected:
	ID3DX11Effect* _effect;
};
