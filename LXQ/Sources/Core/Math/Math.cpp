/**
*	Modified version of DirectXTK SimpleMath. The most major difference is
*we use
* left-hand coordinate system by default.
*
* Copyright (c) Microsoft Corporation. All rights reserved.
*/

#include <algorithm>
#include "Math/Math.h"

/****************************************************************************
 *
 * Constants
 *
 ****************************************************************************/

namespace LXQ {
	namespace Math {
#if defined(_MSC_VER) && (_MSC_VER < 1800)
		const Vector2 Vector2::Zero(0.f, 0.f);
		const Vector2 Vector2::One(1.f, 1.f);
		const Vector2 Vector2::UnitX(1.f, 0.f);
		const Vector2 Vector2::UnitY(0.f, 1.f);

		const Vector3 Vector3::Zero(0.f, 0.f, 0.f);
		const Vector3 Vector3::One(1.f, 1.f, 1.f);
		const Vector3 Vector3::UnitX(1.f, 0.f, 0.f);
		const Vector3 Vector3::UnitY(0.f, 1.f, 0.f);
		const Vector3 Vector3::UnitZ(0.f, 0.f, 1.f);
		const Vector3 Vector3::Up(0.f, 1.f, 0.f);
		const Vector3 Vector3::Down(0.f, -1.f, 0.f);
		const Vector3 Vector3::Right(1.f, 0.f, 0.f);
		const Vector3 Vector3::Left(-1.f, 0.f, 0.f);
		const Vector3 Vector3::Forward(0.f, 0.f, 1.f);
		const Vector3 Vector3::Backward(0.f, 0.f, -1.f);

		const Vector4 Vector4::Zero(0.f, 0.f, 0.f, 0.f);
		const Vector4 Vector4::One(1.f, 1.f, 1.f, 1.f);
		const Vector4 Vector4::UnitX(1.f, 0.f, 0.f, 0.f);
		const Vector4 Vector4::UnitY(0.f, 1.f, 0.f, 0.f);
		const Vector4 Vector4::UnitZ(0.f, 0.f, 1.f, 0.f);
		const Vector4 Vector4::UnitW(0.f, 0.f, 0.f, 1.f);

		const Matrix Matrix::Identity(1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f,
			1.f, 0.f, 0.f, 0.f, 0.f, 1.f);

		const Quaternion Quaternion::Identity(0.f, 0.f, 0.f, 1.f);
#else
		const Vector2 Vector2::Zero = { 0.f, 0.f };
		const Vector2 Vector2::One = { 1.f, 1.f };
		const Vector2 Vector2::UnitX = { 1.f, 0.f };
		const Vector2 Vector2::UnitY = { 0.f, 1.f };

		const Vector3 Vector3::Zero = { 0.f, 0.f, 0.f };
		const Vector3 Vector3::One = { 1.f, 1.f, 1.f };
		const Vector3 Vector3::UnitX = { 1.f, 0.f, 0.f };
		const Vector3 Vector3::UnitY = { 0.f, 1.f, 0.f };
		const Vector3 Vector3::UnitZ = { 0.f, 0.f, 1.f };
		const Vector3 Vector3::Up = { 0.f, 1.f, 0.f };
		const Vector3 Vector3::Down = { 0.f, -1.f, 0.f };
		const Vector3 Vector3::Right = { 1.f, 0.f, 0.f };
		const Vector3 Vector3::Left = { -1.f, 0.f, 0.f };
		const Vector3 Vector3::Forward = { 0.f, 0.f, 1.f };
		const Vector3 Vector3::Backward = { 0.f, 0.f, -1.f };

		const Vector4 Vector4::Zero = { 0.f, 0.f, 0.f, 0.f };
		const Vector4 Vector4::One = { 1.f, 1.f, 1.f, 1.f };
		const Vector4 Vector4::UnitX = { 1.f, 0.f, 0.f, 0.f };
		const Vector4 Vector4::UnitY = { 0.f, 1.f, 0.f, 0.f };
		const Vector4 Vector4::UnitZ = { 0.f, 0.f, 1.f, 0.f };
		const Vector4 Vector4::UnitW = { 0.f, 0.f, 0.f, 1.f };

		const Matrix Matrix::Identity = { 1.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f };

		const Quaternion Quaternion::Identity = { 0.f, 0.f, 0.f, 1.f };

		const Color Color::White = { 1.0f, 1.0f, 1.0f, 1.0f };
		const Color Color::Black = { 0.0f, 0.0f, 0.0f, 1.0f };
		const Color Color::Red = { 1.0f, 0.0f, 0.0f, 1.0f };
		const Color Color::Green = { 0.0f, 1.0f, 0.0f, 1.0f };
		const Color Color::Blue = { 0.0f, 0.0f, 1.0f, 1.0f };
		const Color Color::Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
		const Color Color::Cyan = { 0.0f, 1.0f, 1.0f, 1.0f };
		const Color Color::Magenta = { 1.0f, 0.0f, 1.0f, 1.0f };
		const Color Color::Silver = { 0.75f, 0.75f, 0.75f, 1.0f };
		const Color Color::LightSteelBlue = { 0.69f, 0.77f, 0.87f, 1.0f };
		const Color Color::Grey = { 0.294f, 0.294f, 0.294f, 1.0f };
#endif
	}
}

/****************************************************************************
 *
 * Viewport
 *
 ****************************************************************************/

static_assert(sizeof(LXQ::Math::Viewport) == sizeof(D3D11_VIEWPORT),
	"Size mismatch");
static_assert(FIELD_OFFSET(LXQ::Math::Viewport, x) ==
	FIELD_OFFSET(D3D11_VIEWPORT, TopLeftX),
	"Layout mismatch");
static_assert(FIELD_OFFSET(LXQ::Math::Viewport, y) ==
	FIELD_OFFSET(D3D11_VIEWPORT, TopLeftY),
	"Layout mismatch");
static_assert(FIELD_OFFSET(LXQ::Math::Viewport, width) ==
	FIELD_OFFSET(D3D11_VIEWPORT, Width),
	"Layout mismatch");
static_assert(FIELD_OFFSET(LXQ::Math::Viewport, height) ==
	FIELD_OFFSET(D3D11_VIEWPORT, Height),
	"Layout mismatch");
static_assert(FIELD_OFFSET(LXQ::Math::Viewport, minDepth) ==
	FIELD_OFFSET(D3D11_VIEWPORT, MinDepth),
	"Layout mismatch");
static_assert(FIELD_OFFSET(LXQ::Math::Viewport, maxDepth) ==
	FIELD_OFFSET(D3D11_VIEWPORT, MaxDepth),
	"Layout mismatch");

RECT
LXQ::Math::Viewport::ComputeDisplayArea(DXGI_SCALING scaling,
UINT backBufferWidth,
UINT backBufferHeight, int outputWidth,
int outputHeight)
{
	RECT rct;

	switch (int(scaling)) {
	case DXGI_SCALING_STRETCH:
		// Output fills the entire window area
		rct.top = 0;
		rct.left = 0;
		rct.right = outputWidth;
		rct.bottom = outputHeight;
		break;

	case 2 /*DXGI_SCALING_ASPECT_RATIO_STRETCH*/:
		// Output fills the window area but respects the original aspect ratio,
		// using pillar boxing or letter boxing as required
		// Note: This scaling option is not supported for legacy Win32 windows
		// swap chains
	{
		assert(backBufferHeight > 0);
		float aspectRatio = float(backBufferWidth) / float(backBufferHeight);

		// Horizontal fill
		float scaledWidth = float(outputWidth);
		float scaledHeight = float(outputWidth) / aspectRatio;
		if (scaledHeight >= outputHeight) {
			// Do vertical fill
			scaledWidth = float(outputHeight) * aspectRatio;
			scaledHeight = float(outputHeight);
		}

		float offsetX = (float(outputWidth) - scaledWidth) * 0.5f;
		float offsetY = (float(outputHeight) - scaledHeight) * 0.5f;

		rct.left = static_cast<LONG>(offsetX);
		rct.top = static_cast<LONG>(offsetY);
		rct.right = static_cast<LONG>(offsetX + scaledWidth);
		rct.bottom = static_cast<LONG>(offsetY + scaledHeight);

		// Clip to display window
		rct.left = std::max<LONG>(0, rct.left);
		rct.top = std::max<LONG>(0, rct.top);
		rct.right = std::min<LONG>(outputWidth, rct.right);
		rct.bottom = std::min<LONG>(outputHeight, rct.bottom);
	}
	break;

	case DXGI_SCALING_NONE:
	default:
		// Output is displayed in the upper left corner of the window area
		rct.top = 0;
		rct.left = 0;
		rct.right = std::min<UINT>(backBufferWidth, UINT(outputWidth));
		rct.bottom = std::min<UINT>(backBufferHeight, UINT(outputHeight));
		break;
	}

	return rct;
}

RECT
LXQ::Math::Viewport::ComputeTitleSafeArea(UINT backBufferWidth,
UINT backBufferHeight)
{
	float safew = (float(backBufferWidth) + 9.f) / 10.f;
	float safeh = (float(backBufferHeight) + 9.f) / 10.f;

	RECT rct;
	rct.left = static_cast<LONG>(safew);
	rct.top = static_cast<LONG>(safeh);
	rct.right = static_cast<LONG>(float(backBufferWidth) - safew + 0.5f);
	rct.bottom = static_cast<LONG>(float(backBufferHeight) - safeh + 0.5f);

	return rct;
}
