#pragma once

#include <iostream>
#include <string>
#include <vector>

/**
 * Mixins in C++: Capability-based Composition
 * 
 * While the Decorator pattern focuses on wrapping and extending EXISTING 
 * functionality, Mixins are used to inject NEW, UNRELATED capabilities 
 * (state and methods) into a class.
 */

// --- Capability 1: Logging ---
class LoggingCapability {
public:
    void Log(const std::string& msg) const {
        std::cout << "[LOG] " << msg << std::endl;
    }
};

// --- Capability 2: Identification ---
class IdentifiableCapability {
public:
    void SetId(int id) { id_ = id; }
    int GetId() const { return id_; }
private:
    int id_ = 0;
};

// --- Capability 3: Serialization ---
class SerializableCapability {
public:
    virtual std::string Serialize() const {
        return "Serialized data";
    }
};

// --- Approach A: Variadic Mixin (Multiple Inheritance) ---
// This allows importing any number of unrelated functionalities.
template <typename... Mixins>
class BaseWithMixins : public Mixins... {
public:
    // This class now has all methods from all Mixins
};

// Example: A Task that can Log and has an ID
using LoggedIdentifiableTask = BaseWithMixins<LoggingCapability, IdentifiableCapability>;

// Example: A User that can Log, has an ID, and is Serializable
using FullUser = BaseWithMixins<LoggingCapability, IdentifiableCapability, SerializableCapability>;


// --- Approach B: Template Inheritance (The "Curried" Mixin) ---
// This is often used when mixins need to interact with the base or each other.
template <typename TBase>
class Logged : public TBase {
public:
    using TBase::TBase;
    void Log(const std::string& msg) const {
        std::cout << "[LOG] " << msg << std::endl;
    }
};

template <typename TBase>
class Identified : public TBase {
public:
    using TBase::TBase;
    void SetId(int id) { id_ = id; }
    int GetId() const { return id_; }
private:
    int id_ = 0;
};

// Usage:
class SimpleTask {
public:
    void Execute() { std::cout << "Executing task..." << std::endl; }
};

using SmartTask = Logged<Identified<SimpleTask>>;

/**
 * Key Differences:
 * 1. Decorator: Wraps an object to modify its EXISTING methods (e.g., overriding PrintName).
 * 2. Mixin: Adds NEW, often unrelated methods (e.g., adding Log() or SetId() to a class that didn't have them).
 */
