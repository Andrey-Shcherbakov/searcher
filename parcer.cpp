#include "parcer.hpp"
#include <unistd.h>

parcer:: parcer(int argc, char *argv[]){
    if(argc > 1) {
        tN = 1;
        depth = 1;
        int tracker = 0;
        for (int i = 0; i < argc; i++) {
            switch (argv[i][0]) {
                case '-': {
                    if (argv[i][1] == 'n') {
                        depth = 0;
                        break;
                    }
                    else {
                        tN = 0;
                        std::string help = (std::string) argv[i];
                        help.erase(help.begin(), help.begin() + 2);

                        for (int j = help.length() - 1; j >= 0; j--) tN = tN * 10 + help[j] - '0';
                        break;
                    }
                }
                case 'C': {
                    dir = (std::string) argv[i];
                    tracker = 1;
                    break;
                }
                case '.': {
                    char cwd[256];
                    getcwd(cwd, sizeof(cwd));
                    std::string help = (std::string) argv[i];
                    help.erase(help.begin());
                    dir = (std::string) cwd + help;
                    tracker = 1;
                    break;
                }
                default: {
                    l = (std::string) argv[i];
                    break;
                }
            }
        }
        if (tracker == 0) {
            char cwd[256];
            getcwd(cwd, sizeof(cwd));
            dir = (std::string) cwd;
        }
    }
    else{
        tN = 1;
        l = (std:: string) argv[0];
        depth = 1;
        char cwd[256];
        getcwd(cwd, sizeof(cwd));
        dir = (std::string) cwd;
    }
}