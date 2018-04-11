#pragma once

#include "resources/resource.h"
#include "texture_slots.h"

class CTexture;

// ----------------------------------------------
class CMaterial : public IResource {

public:

	//enum eTextureSlot {
	//	TS_ALBEDO,
	//	TS_LIGHTMAP,
	//	TS_NORMAL,
	//	TS_COUNT
	//};

	const CTexture* textures[TS_NUM_MATERIALS_SLOTS];

	const CRenderTechnique* tech = nullptr;
	bool  cast_shadows = true;

	void activate() const;
	bool create(const std::string& name);
	void debugInMenu() override;
	void onFileChanged(const std::string& filename) override;

protected:

	const ID3D11ShaderResourceView* srvs[TS_COUNT];

};

