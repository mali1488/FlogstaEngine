// A basic vertex shader, intended to help explore light shaders. 

/*
  Use this template to understand how all the values
  are fed to the shaders, which order etc..
  This is for version 100
 */

#version 100

attribute vec3 VertexPosition;
attribute vec3 VertexNormal;
attribute vec2 VertexST;

varying vec4 Position;
varying vec3 Normal;
varying vec2 STCoords;

uniform vec4 LightPosition;
varying vec4 EyeSpaceLightPosition;
varying vec4 EyeSpacePosition;
varying vec4 EyeSpaceObjectPosition;

uniform mat4 WorldMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main(void) {
  // 1. Set up the transformation pipeline. The view matrix is controlled by
  // key presses (may need to alt-tab away from the window and back again before
  // it picks up key presses. Bonus mark for first person to fix this.)
  // Enabling shadow pass rendering will use a perspective projection rather than
  // othergraphic.
  Position = ProjectionMatrix * ViewMatrix * WorldMatrix * vec4(VertexPosition, 0.5); //ProjectionMatrix * ViewMatrix * WorldMatrix * vec4 (VertexPosition, 1);
  // 2. Start passing through some other values.
  Normal = VertexNormal;
  // 3. We need the normal in the space that we will use for lighting. For this
  // exercise we have chosen eye (view) space. 
  Normal = (ViewMatrix * WorldMatrix * vec4 (VertexNormal, 0)).xyz;
  // 4. Now we need other important quantities, also in eye coordinates. The position of
  // the light.
  EyeSpaceLightPosition = ProjectionMatrix * ViewMatrix * LightPosition;
  // 5. And the position of the vertex. But haven't we done this already?
  EyeSpacePosition = ProjectionMatrix * ViewMatrix * WorldMatrix * vec4 (VertexPosition, 1);
  // 13. For spotlights we need a direction vector for the light. We will create
  // a light that always points at the center of the object (origin in object space)
  // by transforming this value in eye coordinates.
  EyeSpaceObjectPosition = ProjectionMatrix * ViewMatrix * WorldMatrix * vec4 (0, 0, 0, 1);
  STCoords = VertexST;
  gl_Position = Position;
}
