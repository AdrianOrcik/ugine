#include "uepch.h"
#include "windows_input.h"

#include "ugine/input/input.h"
#include "ugine/input/key_codes.h"

#include "ugine/application.h"
#include "GLFW/glfw3.h"

namespace Ugine 
{

	//TODO: memory leak
	Input* Input::sInstance_ = DBG_NEW WindowsInput();
	
	bool Ugine::WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Ugine::WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;

	}

	std::pair<float, float> Ugine::WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float Ugine::WindowsInput::GetMouseXImpl()
	{
		auto[x, y] = GetMousePositionImpl();
		return x;
	}

	float Ugine::WindowsInput::GetMouseYImpl()
	{
		auto[x, y] = GetMousePositionImpl();
		return y;
	}

	bool WindowsInput::IsExitButtonPressedImpl()
	{
		return Input::IsKeyPressed(INPUT_KEY_ESCAPE);
	}

}