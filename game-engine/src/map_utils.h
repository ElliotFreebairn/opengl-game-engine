inline glm::ivec3 world_to_grid(glm::vec3 pos) {
    return glm::ivec3(
        (int)std::floor(pos.x),
        (int)std::floor(pos.y),
        (int)std::floor(pos.z)
    );
}

