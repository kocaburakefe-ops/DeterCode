#ifndef NICE_OVERRIDE_H
#define NICE_OVERRIDE_H

// Ana motorun (native-lib.cpp) bu odayı tetiklemesi için gereken şalter
extern "C" void apply_nice_priority_override();

#endif // NICE_OVERRIDE_H
