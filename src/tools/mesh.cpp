#include "object/rotationbody.h"

int main(int argc, char* argv[]){
    if (argc <= 1)
        printf("Usage: ./modeling <output_name>\n");
    else{
        RotationBody* body = static_cast<RotationBody*>(
            Object::loadFile(argv[1])
            );
        body->save2JsonOBJ("output.obj", 100);
        delete body;
    }
    return 0;
}
