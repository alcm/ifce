#include "include/controller.h"

#include "include/execute_algorithms_cmd.h"
#include "include/set_screen_cmd.h"
#include "include/execution_event_handler.h"

bool Controller::Init(ScreenComponent *screen)
{
    if (screen) {
        screen->set_mediator(shared_from_this());
        window_mgr_.SetScreen(screen);
    }

    return true;
}

void Controller::HandleCommand(const ScreenComponent *sender, ICommand *cmd)
{
    try {
        if (auto exec_cmd = dynamic_cast<ExecuteAlgorithmsCmd *>(cmd)) {
            auto listener = std::dynamic_pointer_cast<ExecutionEventHandler>(sender->event_handler());

            runner_.Run(exec_cmd->algorithms(), *listener);
        } else if (auto set_screen_cmd = dynamic_cast<SetScreenCmd *>(cmd)) {
            auto screen = set_screen_cmd->screen();
            screen->set_mediator(shared_from_this());

            auto screen_wdg = dynamic_cast<QWidget *>(screen);
            window_mgr_.SetScreen(screen_wdg);
        }
    } catch (const std::bad_cast &e) {

    }
}
