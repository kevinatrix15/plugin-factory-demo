# Demo: Plugin Factory design pattern

## What is this?

> Note: I don't know if this pattern has an official name or not, but I've
> chosen to call it "Plugin Factory" because it's a combination of the Factory
> pattern with self-registering types in separate libraries.

This implements a minimal example of a Plugin Factory (or a Factory Plugin?), which is a method of
creating a Factory in one library, custom types in another library, and a 3rd library which can
auto-register all of the custom types for you.

The pattern was inspired by / based off of the BehaviorTreeFactory in [BehaviorTree.CPP](https://github.com/BehaviorTree/BehaviorTree.CPP).

## What does it do?

The factory library defines an abstract base class, and a Factory class which can "build" (instantiate) instances of this base class (specifically, derived classes) given an ID associated with a specific type.

Because the base class has just a single default constructor with no arguments, derived classes with custom constructors require special handling - hence the Factory uses a "builder" function associated with each ID to create it.

The "builder" function is actually a lambda created elsewhere that captures the desired arguments to the constructor of the derived type, and when invoked, creates and returns an instance of the derived type using the captured arguments.

To manage the complexity of registering these derived types with custom constructors, a registry library defines some boilerplate to aid in auto-magically registering types into the Factory.
When creating a new derived type, all that needs to happen is to call `REGISTER_TYPE(type_name)` and the type will be added to the registry.
Then, in the executable, you call `MyTypeRegistry::RegisterAll()`, passing in the Factory and the custom constructor arguments, and the Registry library does the work of registering the types _and their builder functions_ into the Factory for later use.

## Cool, so what's the problem?

The problem is that if your executable doesn't directly _use_ any of the symbols defined in the custom types library, library _will not be loaded_, and all of the types defined in that library _will not be registered_.
