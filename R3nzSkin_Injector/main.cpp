#include <Windows.h>
#include <thread>

#include "R3nzUI.hpp"
#include "Injector.hpp"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Threading;
[STAThread]

int main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	R3nzSkinInjector::R3nzUI form;

	auto thread{ std::thread(Injector::run) };
	Thread^ screenThread = gcnew Thread(gcnew ThreadStart(%form, &R3nzSkinInjector::R3nzUI::updateScreen));
	screenThread->Start();

	Application::Run(% form);

	thread.detach();
	screenThread->Abort();

	return EXIT_SUCCESS;
}
