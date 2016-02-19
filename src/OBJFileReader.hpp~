//  Created by Mattias on 2015-09-29.
//  Copyright © 2015 Mattias. All rights reserved.

#pragma once

#include <glm/glm.hpp>
#include <stdint.h>
#include <vector>
#include <GL/glew.h>

namespace cgtk {
    /* Internal structure */
    
    //! @class OBJFileReader OBJFileReader.h OBJFileReader.h
    //!
    //! @brief OBJ file reader class
    //!
    //! Reads a 3D model (represented as an indexed triangle mesh) from a
    //! wavefront .obj (OBJ) file.
    //!
    class OBJFileReader {
    public:
        //! Constructor
        //!
        OBJFileReader();
        
        //! Destructor
        //!
        ~OBJFileReader();
        
        //! Execute the reader.
        //!
        //! @param[in] filename The name of the OBJ file to be read.
        //! @return true if the reading succeeded, otherwise false.
        //!
        bool load(const char *filename, int n);
        
        //! Get the vertices of the 3D model.
        //!
        //! @return An array of vertices.
        //!
        std::vector<glm::vec3> const &getVertices() const;
        
        //! Get the per-vertex normals of the 3D model.
        //!
        //! @return An array of normal vectors.
        //!
        std::vector<glm::vec3> const &getNormals() const;
        
        //! Get the element indices of the 3D model.
        //!
        //! @return An array of element indices.
        //!
        std::vector<uint32_t> const &getIndices() const;
        
        std::vector<glm::vec2> const &getUvs() const;
        std::vector<GLfloat> const &getFloatVectices() const;
        std::vector<GLfloat> const &getFloatUvs() const;
        std::vector<uint32_t> const &getUvIndices() const;
        std::vector<glm::vec2> const &getUvsOriginal() const;
        
    private:
        std::vector<glm::vec3> mVertices;
        std::vector<glm::vec3> mNormals;
        std::vector<glm::vec2> mUv;
        std::vector<glm::vec2> uvsOriginal;
        
        std::vector<uint32_t> mIndices;
        std::vector<uint32_t> mUvIndices;
        std::vector<uint32_t> mNormalIndices;
        std::vector<float> fVertices;
        std::vector<float> fUvs;
        
    };
}