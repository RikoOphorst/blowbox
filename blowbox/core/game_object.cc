//#include "game_object.h"
//
//namespace blowbox
//{
//	//------------------------------------------------------------------------------------------------------
//	GameObject::GameObject() :
//		position_({ 0.0f, 0.0f, 0.0f, 1.0f }),
//		rotation_({ 0.0f, 0.0f, 0.0f, 1.0f }),
//		scale_({ 1.0f, 1.0f, 1.0f, 1.0f }),
//		anchor_({ 0.0f, 0.0f, 0.0f, 1.0f }),
//		alpha_(1.0f)
//	{
//
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	GameObject::~GameObject()
//	{
//
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	GameObject* GameObject::Create()
//	{
//		return new GameObject();
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	void GameObject::SetPosition(const XMVECTOR& position)
//	{
//		position_ = position;
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	void GameObject::SetPosition(float& x, float& y, float& z)
//	{
//		position_ = { x, y, z, 1.0f };
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	void GameObject::TranslateBy(const XMVECTOR& translation)
//	{
//		position_ += translation;
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	void GameObject::TranslateBy(float& x, float& y, float& z)
//	{
//		position_ += { x, y, z, 1.0f };
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	void GameObject::SetRotation(const XMVECTOR& rotation)
//	{
//		rotation_ = rotation;
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	void GameObject::SetRotation(float& x, float& y, float& z)
//	{
//		rotation_ = { x, y, z, 1.0f };
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	void GameObject::RotateBy(const XMVECTOR& rotation)
//	{
//		rotation_ += rotation;
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	void GameObject::RotateBy(float& x, float& y, float& z)
//	{
//		rotation_ += { x, y, z, 1.0f };
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	void GameObject::SetScale(const XMVECTOR& scale)
//	{
//		scale_ = scale;
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	void GameObject::SetScale(float& x, float& y, float& z)
//	{
//		scale_ = { x, y, z, 1.0f };
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	void GameObject::ScaleBy(const XMVECTOR& scale)
//	{
//		scale_ += scale;
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	void GameObject::ScaleBy(float& x, float& y, float& z)
//	{
//		scale_ += { x, y, z, 1.0f };
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	void GameObject::SetAnchor(const XMVECTOR& anchor)
//	{
//		anchor_ = anchor;
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	void GameObject::SetAnchor(float& x, float& y, float& z)
//	{
//		anchor_ = { x, y, z, 1.0f };
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	void GameObject::SetAlpha(const float& a)
//	{
//		alpha_ = a;
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	const XMVECTOR& GameObject::GetPosition() const
//	{
//		return position_;
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	const XMVECTOR& GameObject::GetRotation() const
//	{
//		return rotation_;
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	const XMVECTOR& GameObject::GetScale() const
//	{
//		return scale_;
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	const XMVECTOR& GameObject::GetAnchor() const
//	{
//		return anchor_;
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	const float& GameObject::GetAlpha() const
//	{
//		return alpha_;
//	}
//
//	//------------------------------------------------------------------------------------------------------
//	XMMATRIX GameObject::GetWorld() const
//	{
//		return XMMatrixScalingFromVector(scale_) * XMMatrixTranslationFromVector(anchor_ * scale_) * XMMatrixRotationRollPitchYawFromVector(rotation_) * XMMatrixTranslationFromVector(position_);
//	}
//}