#include "MyApp.h"
#include "MainFrame.h"
#include "functiiBazaDeDate.h"


bool MyApp::OnInit() {
    MainFrame *frame = new MainFrame("Recipe Manager");
    frame->Show(true);
    return true;
}


wxIMPLEMENT_APP(MyApp);