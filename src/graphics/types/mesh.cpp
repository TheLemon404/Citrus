#include "mesh.hpp"

namespace Citrus {
    std::vector<float> Mesh::ExtractPositionData() {
        return {
            -0.5, -0.5, 0.0,
            +0.5, -0.5, 0.0,
            +0.5, +0.5, 0.0,
            -0.5, +0.5, 0.0,
        };

        /*
        std::vector<float> data;
        for (int i = 0; i < vertices.size(); i++) {
            data.push_back(vertices[i].position.x);
            data.push_back(vertices[i].position.y);
            data.push_back(vertices[i].position.z);
        }
        */
    }

    std::vector<float> Mesh::ExtractNormalData() {
        std::vector<float> data;
        for (int i = 0; i < vertices.size(); i++) {
            data.push_back(vertices[i].normal.x);
            data.push_back(vertices[i].normal.y);
            data.push_back(vertices[i].normal.z);
        }
    }

    std::vector<float> Mesh::ExtractColorData() {
        return {
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
            1.0, 1.0, 0.0,
        };

        /*
        std::vector<float> data;
        for (int i = 0; i < vertices.size(); i++) {
            data.push_back(vertices[i].color.x);
            data.push_back(vertices[i].color.y);
            data.push_back(vertices[i].color.z);
        }
        */
    }

    std::vector<float> Mesh::ExtractUVData() {
        std::vector<float> data;
        for (int i = 0; i < vertices.size(); i++) {
            data.push_back(vertices[i].uv.x);
            data.push_back(vertices[i].uv.y);
        }
    }
}