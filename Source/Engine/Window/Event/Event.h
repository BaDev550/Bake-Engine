#pragma once
#include "Engine/Defines/Types.h"
#include <string>
#include <string_view>

namespace Bake {
	enum class EventType : u8 {
		None,
		EngineTick,

		KeyPressed,
		KeyReleased,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled,

		WindowClosed,
		WindowResized,
		WindowFocused,
		WindowLostFocus
	};

	enum class EventCategory : u8 {
		None = 0,
		Engine =	BIT(0),
		Window =	BIT(1),
		Keyboard =	BIT(2),
		Mouse =		BIT(3)
	};

	class EventBase {
	public:
		virtual ~EventBase() = default;
		virtual std::string_view GetName() const = 0;
		virtual EventType GetEventType() const = 0;
		virtual EventCategory GetEventCategory() const = 0;

		bool IsInCategory(EventCategory category) const { return (static_cast<u8>(GetEventCategory()) & static_cast<u8>(category)) != 0; }
	};

	template<class Derived>
	class Event : public EventBase {
	public:
		virtual ~Event() = default;

		virtual std::string_view GetName() const override final { return static_cast<const Derived*>(this)->Impl_GetName(); }
		virtual EventType GetEventType() const override final { return static_cast<const Derived*>(this)->Impl_GetType(); }
		virtual EventCategory GetEventCategory() const override final { return static_cast<const Derived*>(this)->Impl_GetCategory(); }
	};
#define GENERATED_EVENT(type, category) std::string_view Impl_GetName() const { return #type; } \
										EventType Impl_GetType() const { return EventType::type; } \
										EventCategory Impl_GetCategory() const { return EventCategory::category; }

	class WindowResizedEvent : public Event<WindowResizedEvent> {
	public:
		GENERATED_EVENT(WindowResized, Window);

		WindowResizedEvent(u32 width, u32 height) : _width(width), _height(height) {}
		[[nodiscard]] u32 GetWidth() const { return _width; }
		[[nodiscard]] u32 GetHeight() const { return _height; }
	private:
		u32 _width, _height;
	};

	class WindowClosedEvent : public Event<WindowClosedEvent> { public: GENERATED_EVENT(WindowClosed, Window); };
	class WindowFocusedEvent : public Event<WindowFocusedEvent> { public: GENERATED_EVENT(WindowFocused, Window); };
	class WindowLostFocusEvent : public Event<WindowLostFocusEvent> { public: GENERATED_EVENT(WindowLostFocus, Window); };

	class KeyPressedEvent : public Event<KeyPressedEvent> {
	public:
		GENERATED_EVENT(KeyPressed, Keyboard);

		KeyPressedEvent(u32 keycode) : _keyCode(keycode) {}

		[[nodiscard]] u32 GetKeyCode() const { return _keyCode; }
	private:
		u32 _keyCode;
	};

	class KeyReleasedEvent : public Event<KeyReleasedEvent> {
	public:
		GENERATED_EVENT(KeyReleased, Keyboard);

		KeyReleasedEvent(u32 keycode) : _keyCode(keycode) {}

		[[nodiscard]] u32 GetKeyCode() const { return _keyCode; }
	private:
		u32 _keyCode;
	};
}