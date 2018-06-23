#pragma once
#include <vector>

class PipelineData {
    public:
        PipelineData();
        PipelineData(PipelineData&& that) noexcept;
        PipelineData(const PipelineData&) = delete;
        PipelineData &operator=(const PipelineData&) = delete;
        ~PipelineData();
        void initVertexArray();
        void initVertexBuffer(std::vector<float > data);
        void initElementArray(std::vector<unsigned int> data);
        const unsigned int get_vertex_array_id() const;
        const unsigned int get_vertex_buffer_id() const;
    private:
        unsigned int m_vertex_array_id;
        unsigned int m_vertex_buffer_id;
        unsigned int m_element_buffer_id;
};
