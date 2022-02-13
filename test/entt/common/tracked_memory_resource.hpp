#ifndef ENTT_COMMON_TRACKED_MEMORY_RESOURCE_HPP
#define ENTT_COMMON_TRACKED_MEMORY_RESOURCE_HPP

#ifdef ENTT_HAS_HEADER_VERSION
#    include <version>
#
#    if defined(__cpp_lib_memory_resource) && __cpp_lib_memory_resource >= 201603L
#        define ENTT_HAS_TRACKED_MEMORY_RESOURCE
#
#        include <cstddef>
#        include <memory_resource>
#        include <string>
#        include <entt/config/config.h>

namespace test {

class tracked_memory_resource: public std::pmr::memory_resource {
    void *do_allocate(std::size_t bytes, std::size_t alignment) override {
        ++alloc_counter;
        return std::pmr::get_default_resource()->allocate(bytes, alignment);
    }

    void do_deallocate(void *value, std::size_t bytes, std::size_t alignment) override {
        ++dealloc_counter;
        std::pmr::get_default_resource()->deallocate(value, bytes, alignment);
    }

    bool do_is_equal(const std::pmr::memory_resource &) const ENTT_NOEXCEPT override {
        return true;
    }

public:
    using string_type = std::pmr::string;
    using size_type = std::size_t;

    size_type do_allocate_counter() const ENTT_NOEXCEPT {
        return alloc_counter;
    }

    size_type do_deallocate_counter() const ENTT_NOEXCEPT {
        return dealloc_counter;
    }

    void reset() ENTT_NOEXCEPT {
        alloc_counter = 0u;
        dealloc_counter = 0u;
    }

private:
    size_type alloc_counter{};
    size_type dealloc_counter{};
};

} // namespace test

#    endif
#endif

#endif
