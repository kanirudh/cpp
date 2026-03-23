#include <gtest/gtest.h>
#include "design_patterns/Mixin.h"

// Test using Variadic Mixins (Approach A)
TEST(MixinTest, VariadicMixin) {
    LoggedIdentifiableTask task;
    
    // Capability 1: Logging (Unrelated to identification)
    task.Log("Test log message");
    
    // Capability 2: Identification (Unrelated to logging)
    task.SetId(101);
    EXPECT_EQ(task.GetId(), 101);
}

// Test using Template Inheritance Mixins (Approach B)
TEST(MixinTest, TemplateInheritanceMixin) {
    SmartTask task;
    
    // This class didn't have Execute() originally, 
    // it was passed in as the Base.
    task.Execute();
    
    // Now it also has these "mixed-in" capabilities:
    task.Log("Executing smart task");
    task.SetId(42);
    EXPECT_EQ(task.GetId(), 42);
}

// Test using full composition
TEST(MixinTest, FullUserMixin) {
    FullUser user;
    
    user.Log("User login");
    user.SetId(123);
    EXPECT_EQ(user.GetId(), 123);
    
    // Capability 3: Serialization (Orthogonal functionality)
    EXPECT_EQ(user.Serialize(), "Serialized data");
}

// Demonstrate orthogonality:
// We can mix in only what we need for a specific class.
TEST(MixinTest, PartialMixin) {
    using LoggedOnlyTask = BaseWithMixins<LoggingCapability>;
    LoggedOnlyTask task;
    task.Log("Only logging here");
    
    // task.SetId(1); // This would fail to compile (as intended)
}
