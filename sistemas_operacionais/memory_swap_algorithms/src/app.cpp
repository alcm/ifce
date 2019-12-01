#include "include/app.h"

#include <fstream>
#include <sstream>

#include "include/algorithm_execution_screen.h"
#include "include/controller.h"

App::App(int &argc, char **argv)
    : QApplication{argc, argv},
      controller_{std::make_shared<Controller>()}
{

}

std::vector<swapping_algorithms::MemOperation> App::ParseFile(const std::string &filepath)
{
    std::stringstream file_content;

    file_content << std::ifstream(filepath).rdbuf();

    std::string buffer;
    std::vector<swapping_algorithms::MemOperation> data;
    for (auto ch : file_content.str()) {
        if (ch == '-') {
            data.emplace_back(swapping_algorithms::MemOperation{ std::atoi(buffer.substr().c_str()),
                                                                 buffer.at(buffer.size() - 1) });
            buffer.clear();
        } else
            buffer.push_back(ch);
    }

    return data;
}


int App::Run(int q1, int q2, int bit_r, const std::string &file_path)
{
    auto screen = new AlgorithmExecutionScreen(q1, q2, bit_r, ParseFile(file_path));
    if (controller_->Init(screen))
        return exec();

    return -1;
}
