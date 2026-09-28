#pragma once

#include "../CoreInc.h"
#include "RenderSettings.h"


struct Shader;
class Window;
class MeshData;

class RenderDevice : public Object
{
public:
	//! Destructor
	~RenderDevice() override = default;


	//=========
	// Events
	//=========

	virtual bool DeviceInit(Window& window);


	//=========
	// Render
	//=========

	virtual void PreRender()  = 0;
	virtual void PostRender() = 0;


	//===============
	// Mesh Helpers
	//===============

	virtual UUID& CreateMesh(const MeshData& meshData) = 0;
	virtual void DrawMesh(UUID& mesh, UUID& shader) = 0;
	virtual void DestroyMesh(UUID& mesh) = 0;


	//=================
	// Shader Helpers
	//=================

	virtual UUID& CreateShader(const Shader& shader) = 0;
	virtual void SetMainShader(UUID& shader) = 0;
	virtual void SetPresentShader(UUID& shader) = 0;
	virtual void DestroyShader(UUID& shader) = 0;


	//=========================
	// Shader Uniform Helpers
	//=========================

	virtual void SetShaderBool		(UUID& shaderHandle, const String& name, bool	  value) = 0;

	virtual void SetShaderInt		(UUID& shaderHandle, const String& name, int32	  value) = 0;
	virtual void SetShaderUInt		(UUID& shaderHandle, const String& name, uint32	  value) = 0;

	virtual void SetShaderFloat		(UUID& shaderHandle, const String& name, float	  value) = 0;
	virtual void SetShaderDouble	(UUID& shaderHandle, const String& name, double	  value) = 0;

	//virtual void SetShaderIVec2	(UUID& shaderHandle, const String& name, Vector2I value) = 0;
	//virtual void SetShaderUVec2	(UUID& shaderHandle, const String& name, Vector2U value) = 0;
	//virtual void SetShaderVec2	(UUID& shaderHandle, const String& name, Vector2F value) = 0;
	//virtual void SetShaderDVec2	(UUID& shaderHandle, const String& name, Vector2  value) = 0;

	//virtual void SetShaderIVec3	(UUID& shaderHandle, const String& name, Vector3I value) = 0;
	//virtual void SetShaderUVec3	(UUID& shaderHandle, const String& name, Vector3U value) = 0;
	virtual void SetShaderVec3		(UUID& shaderHandle, const String& name, Vector3F value) = 0;
	virtual void SetShaderDVec3		(UUID& shaderHandle, const String& name, Vector3  value) = 0;

	//virtual void SetShaderIVec4	(UUID& shaderHandle, const String& name, Vector4I value) = 0;
	//virtual void SetShaderUVec4	(UUID& shaderHandle, const String& name, Vector4U value) = 0;
	virtual void SetShaderVec4		(UUID& shaderHandle, const String& name, Vector4F value) = 0;
	virtual void SetShaderDVec4		(UUID& shaderHandle, const String& name, Vector4  value) = 0;

	virtual void SetShaderMat4		(UUID& shaderHandle, const String& name, Matrix4F value) = 0;
	virtual void SetShaderDMat4		(UUID& shaderHandle, const String& name, Matrix4  value) = 0;

	virtual void SetViewUniform		 (const Matrix4F& view)		  = 0;
	virtual void SetProjectionUniform(const Matrix4F& projection) = 0;
	virtual void SetModelUniform	 (const Matrix4F& model)	  = 0;


	//==================
	// Render Settings
	//==================

	virtual void ApplySettings(const RenderSettings& settings) = 0;
	virtual void SetHDR(bool enabled) = 0;
	virtual void SetAA(const AAMode& mode, uint8 samples) = 0;
	virtual void SetVSync(const VSyncMode& mode) = 0;


	//===============
	// Misc Helpers
	//===============

	virtual void PrintRendererInfo() = 0;


private:
	virtual bool CreateHDRFramebuffer(int32 width, int32 height) = 0;
	virtual bool ResizeHDRFramebuffer(int32 width, int32 height) = 0;
	virtual void DestroyHDRFramebuffer() = 0;

	virtual bool CreatePresentResources() = 0;
	virtual void DestroyPresentResources() = 0;

	virtual void PresentFrame(UUID& presentShader) = 0;

	virtual void UpdateHDROutputState() = 0;
};