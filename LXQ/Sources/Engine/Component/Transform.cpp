#include "Transform.h"
#include "GameObject.h"


Transform::Transform()
{
}


Transform::~Transform()
{
}

void Transform::SetParentTransform(const Transform* parentTransform)
{
	_parentTransform = parentTransform;
}

void Transform::SetLocalMatrix(const Math::Matrix& value)
{
	auto matrix = value;
	Math::Vector3 pos, scale;
	Math::Quaternion qrot;

	if (matrix.Decompose(scale, qrot, pos))
	{
		_position = pos;
		_scale = scale;
		_rotation = qrot.GetPitchYawRollVector();
	}
}

void Transform::SetPosition(const Math::Vector3& value)
{
	auto r = Math::Matrix::CreateFromYawPitchRoll(_rotation.y, _rotation.x, _rotation.z);
	auto s = Math::Matrix::CreateScale(_scale);
	auto t = Math::Matrix::CreateTranslation(value);
	SetMatrix(r * s * t);
}

void Transform::SetRotation(const Math::Vector3& value)
{
	auto r = Math::Matrix::CreateFromYawPitchRoll(value.y, value.x, value.z);
	auto s = Math::Matrix::CreateScale(_scale);
	auto t = Math::Matrix::CreateTranslation(_position);
	SetMatrix(r * s * t);
}

void Transform::SetScale(const Math::Vector3& value)
{
	auto r = Math::Matrix::CreateFromYawPitchRoll(_rotation.y, _rotation.x, _rotation.z);
	auto s = Math::Matrix::CreateScale(value);
	auto t = Math::Matrix::CreateTranslation(_position);
	SetMatrix(r * s * t);
}

void Transform::SetMatrix(const Math::Matrix& value)
{
	if (_parentTransform)
	{
		// calculate inverted parent world matrix
		Math::Matrix parentMatrix = _parentTransform->GetMatrix();
		parentMatrix.Invert(parentMatrix);

		// local matrix = world matrix * inverted parent world matrix
		Math::Matrix matrix = value * parentMatrix;
		SetLocalMatrix(matrix);
	}
	else
	{
		SetLocalMatrix(value);
	}
}

Math::Matrix Transform::GetLocalMatrix() const
{
	auto r = Math::Matrix::CreateFromYawPitchRoll(_rotation.y, _rotation.x, _rotation.z);
	auto s = Math::Matrix::CreateScale(_scale);
	auto t = Math::Matrix::CreateTranslation(_position);
	return r * s * t;
}

Math::Vector3 Transform::GetLocalUpVec() const
{
	auto rotation = GetLocalRotation();
	auto matrix = Math::Matrix::CreateFromYawPitchRoll(rotation.y, rotation.x, rotation.z);
	return Math::Vector3::TransformNormal(Math::Vector3::Up, matrix);
}

Math::Vector3 Transform::GetLocalRightVec() const
{
	auto rotation = GetLocalRotation();
	auto matrix = Math::Matrix::CreateFromYawPitchRoll(rotation.y, rotation.x, rotation.z);
	return Math::Vector3::TransformNormal(Math::Vector3::Right, matrix);
}

Math::Vector3 Transform::GetLocalForwardVec() const
{
	auto rotation = GetLocalRotation();
	auto matrix = Math::Matrix::CreateFromYawPitchRoll(rotation.y, rotation.x, rotation.z);
	return Math::Vector3::TransformNormal(Math::Vector3::Forward, matrix);
}

Math::Matrix Transform::GetMatrix() const
{
	if (_parentTransform)
		return GetLocalMatrix() * _parentTransform->GetMatrix();
	else
		return GetLocalMatrix();
}

Math::Vector3 Transform::GetPosition() const
{
	auto matrix = GetMatrix();
	Math::Vector3 pos, scale;
	Math::Quaternion qrot;

	matrix.Decompose(scale, qrot, pos);
	return pos;
}

Math::Vector3 Transform::GetRotation() const
{
	auto matrix = GetMatrix();
	Math::Vector3 pos, scale;
	Math::Quaternion qrot;

	matrix.Decompose(scale, qrot, pos);
	return qrot.GetPitchYawRollVector();
}

Math::Vector3 Transform::GetScale() const
{
	auto matrix = GetMatrix();
	Math::Vector3 pos, scale;
	Math::Quaternion qrot;

	matrix.Decompose(scale, qrot, pos);
	return scale;
}

Math::Vector3 Transform::GetUpVec() const
{
	auto rotation = GetRotation();
	auto matrix = Math::Matrix::CreateFromYawPitchRoll(rotation.y, rotation.x, rotation.z);
	return Math::Vector3::TransformNormal(Math::Vector3::Up, matrix);
}

Math::Vector3 Transform::GetRightVec() const
{
	auto rotation = GetRotation();
	auto matrix = Math::Matrix::CreateFromYawPitchRoll(rotation.y, rotation.x, rotation.z);
	return Math::Vector3::TransformNormal(Math::Vector3::Right, matrix);
}

Math::Vector3 Transform::GetForwardVec() const
{
	auto rotation = GetRotation();
	auto matrix = Math::Matrix::CreateFromYawPitchRoll(rotation.y, rotation.x, rotation.z);
	return Math::Vector3::TransformNormal(Math::Vector3::Forward, matrix);
}

std::string Transform::ToString()
{
	char tmp[256];
	sprintf_s(tmp, "pos%s, rot%s, scale%s", GetPosition().ToString().c_str(), GetRotation().ToString().c_str(), GetScale().ToString().c_str());
	return tmp;
}

void Transform::OnAttach(GameObject* holder)
{
	IComponent::OnAttach(holder);

	this->TryAttachParent();

	holder->EventParentChanged.Register(this, [this](GameObject* oldParent){
		this->TryAttachParent();
	});
}

void Transform::OnDetach()
{
	_holder->EventParentChanged.Unregister(this);

	IComponent::OnDetach();
}

void Transform::OnEventHolderParentChanged(GameObject* oldParent)
{
	this->TryAttachParent();
}

bool Transform::TryAttachParent()
{
	auto parent = _holder->GetParent();
	if (parent)
	{ 
		auto parentTransform = parent->GetTransform();
		if (parentTransform)
		{
			this->SetParentTransform(parentTransform);
			return true;
		}
	}

	this->SetParentTransform(nullptr);
	return false;
}
