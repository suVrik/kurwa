#pragma once
#include <vector>

class PipelineData {
    public:
        PipelineData();
        ~PipelineData();
        void initVertexArray();
        void initVertexBuffer(std::vector<float > data);
        void initElementArray(std::vector<unsigned int> data);
        const unsigned int get_vertex_array_id() const;
        const unsigned int get_vertex_buffer_id() const;
    private:
        unsigned int vertex_array_id;
        unsigned int vertex_buffer_id;
        unsigned int element_buffer_id;
};
