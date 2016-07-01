#pragma once

#include "IComponent.h"
#include "Math/Math.h"


/*!
 * \class Transform
 *
 * \brief ±ä»»×é¼þ
 */
class Transform : public IComponent
{
	OBJECT_DECLARE(Transform);
public:
	Transform();
	~Transform();

	void SetParentTransform(const Transform* parentTransform);
	const Transform* getParentTransform() const { return _parentTransform; }
	
	// Set Local Components
	void SetLocalPosition(const Math::Vector3& value) { _position = value; }
	void SetLocalRotation(const Math::Vector3& value) { _rotation = value; }
	void SetLocalScale(const Math::Vector3& value) { _scale = value; }
	void SetLocalMatrix(const Math::Matrix& value);

	// Set World Components
	void SetPosition(const Math::Vector3& value);
	void SetRotation(const Math::Vector3& value);
	void SetScale(const Math::Vector3& value);
	void SetMatrix(const Math::Matrix& value);

	// Get Local Componetns
	Math::Matrix GetLocalMatrix() const;
	Math::Vector3 GetLocalUpVec() const;
	Math::Vector3 GetLocalRightVec() const;
	Math::Vector3 GetLocalForwardVec() const;
	const Math::Vector3& GetLocalPosition() const { return _position; }
	const Math::Vector3& GetLocalRotation() const { return _rotation; }
	const Math::Vector3& GetLocalScale() const { return _scale; }

	// Get World Components
	Math::Matrix GetMatrix() const;
	Math::Vector3 GetPosition() const;
	Math::Vector3 GetRotation() const;
	Math::Vector3 GetScale() const;
	Math::Vector3 GetUpVec() const;
	Math::Vector3 GetRightVec() const;
	Math::Vector3 GetForwardVec() const;

	std::string ToString();

protected:
	void OnAttach(GameObject* holder);
	void OnDetach();

	void OnEventHolderParentChanged(GameObject* parent);

	bool TryAttachParent();

protected:
	const Transform* _parentTransform;

	Math::Vector3 _position		= Math::Vector3::Zero;
	Math::Vector3 _rotation		= Math::Vector3::Zero;
	Math::Vector3 _scale		= Math::Vector3::One;
};

