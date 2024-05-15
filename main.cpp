#include "Option.h"

int main(int argc, char *argv[]) {
    auto x = SomeMove(argv);
    printf("%s", *x.Unwrap());

}
