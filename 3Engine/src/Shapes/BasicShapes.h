/*
 * File BasicShapes.h in project 3EngineGlobal
 * 
 * Copyright (C) Ricardo Rodrigues 2018 - All Rights Reserved
 */
#ifndef INC_3ENGINEGLOBAL_BASICSHAPES_H
#define INC_3ENGINEGLOBAL_BASICSHAPES_H

#include <memory>
#include "Mesh.h"

namespace ThreeEngine {

    class BasicShapes {
        private:
            BasicShapes();

        public:

            /**
             * Creates a Triangle Mesh.
             * @remarks This method only initializes the Vertices in the Mesh. NORMALS ARE NOT CREATED!
             * @param width of the mesh
             * @return Shared Pointer to the created Mesh
             */
            static std::shared_ptr<Mesh> Triangle(float width = 1.0f);

            /**
             * Creates a Square Mesh.
             * @remarks This method only initializes the Vertices in the Mesh. NORMALS ARE NOT CREATED!
             * @param width of the mesh
             * @return Shared Pointer to the created Mesh
             */
            static std::shared_ptr<Mesh> Square(float width = 1.0f);

            /**
             * Creates a Parallelogram Mesh.
             * @remarks This method only initializes the Vertices in the Mesh. NORMALS ARE NOT CREATED!
             * @param width of the mesh
             * @return Shared Pointer to the created Mesh
             */
            static std::shared_ptr<Mesh> Parallelogram(float width = 1.5f);
            /**
             * Creates a Cube Mesh.
             * @remarks This method only initializes the Vertices in the Mesh. NORMALS ARE NOT CREATED!
             * @param width of the Cube
             * @return Shared Pointer to the created Cube Mesh
             */
            static std::shared_ptr<Mesh> Cube(float width = 1.0f);

            /**
             * Creates a Triangular Parallelepiped Mesh.
             * @remarks This method only initializes the Vertices in the Mesh. NORMALS ARE NOT CREATED!
             * @param width of the mesh
             * @return Shared Pointer to the created Mesh
             */
            static std::shared_ptr<Mesh> TriangularParallelepiped(float width = 1.0f);

            /**
             * Creates a Squared Parallelepiped Mesh.
             * @remarks This method only initializes the Vertices in the Mesh. NORMALS ARE NOT CREATED!
             * @param width of the mesh
             * @return Shared Pointer to the created Mesh
             */
            static std::shared_ptr<Mesh> SquaredParallelepiped(float width = 1.5f);
    };

} /* namespace 3EngineGlobal */

#endif //INC_3ENGINEGLOBAL_BASICSHAPES_H
