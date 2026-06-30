#pragma once

#include <typeindex>
#include <string>
#include <string_view>

namespace Bake {
	struct SubsystemReport {
		SubsystemReport() = default;
		SubsystemReport(std::string_view message) : _message(message) {}

		explicit operator bool() const { return _message.empty(); }
		std::string_view GetMessage() const { return _message; }
	private:
		std::string _message;
	};

	class Engine;
	class Subystem {
	public:
		virtual ~Subystem() = default;

		virtual SubsystemReport OnCreate(Engine* engine) { _engine = engine; return SubsystemReport(); }
		virtual void OnUpdate() {}
		virtual void OnDestroy() {}

		const std::type_info& GetTypeID() { return typeid(*this); }
	protected:
		Engine* _engine;
	};
}