#include "ufm.h"

#include <pxr/usd/usd/usdaFileFormat.h>
#include <pxr/usd/sdf/layer.h>
#include <pxr/usd/sdf/primSpec.h>
#include <pxr/usd/sdf/valueTypeName.h>
#include <pxr/usd/sdf/path.h>
#include <pxr/usd/usd/stage.h>
#include <pxr/base/tf/fileUtils.h>
#include <pxr/base/tf/registryManager.h>
#include <pxr/usd/pcp/dynamicFileFormatContext.h>
#include <pxr/usd/usdGeom/cube.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdGeom/xform.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>

#include <iostream>

#include <OpenImageIO/imageio.h>

PXR_NAMESPACE_USING_DIRECTIVE

TF_DEFINE_PUBLIC_TOKENS(ufmTokens, UFM_TOKENS);
TF_DEFINE_PUBLIC_TOKENS(ufmParamNames, UFM_PARAM_NAMES);

TF_REGISTRY_FUNCTION(TfType) 
{
    SDF_DEFINE_FILE_FORMAT(ufm, SdfFileFormat);
}

ufm::ufm()
    : SdfFileFormat(
        ufmTokens->Id, 
        ufmTokens->Version,
        ufmTokens->Target,
        ufmTokens->Extension)
{ 
    //std::cout << "(U)sd(F)rom(M)etadata FileFormat plugin Initialized" << std::endl;
}

ufm::~ufm()
{
}

bool ufm::CanRead(const std::string& i_file) const
{
    return true;
}

bool ufm::Read(pxr::SdfLayer* io_layer,
    const std::string& i_resolvedPath,
    bool i_metadataOnly) const 
{
    if (!TF_VERIFY(io_layer)) {
        return false;
    }
    
    pxr::SdfFileFormat::FileFormatArguments args;
    std::string layerPath;
    pxr::SdfLayer::SplitIdentifier(io_layer->GetIdentifier(), &layerPath, &args);

    auto in = OIIO::ImageInput::open(layerPath.c_str());
    const OIIO::ImageSpec& spec = in->spec();
    std::string usdData = spec.get_string_attribute("usd:data", "");
    in->close();

    pxr::SdfLayerRefPtr newLayerPtr = pxr::SdfLayer::CreateAnonymous(".usd");
    newLayerPtr->ImportFromString(usdData);
    io_layer->TransferContent(newLayerPtr);
    return true;
}

bool ufm::WriteToString( const SdfLayer& layer, std::string* str, const std::string& comment) const
{
    return SdfFileFormat::FindById(ufmTokens->Id)->WriteToString(layer, str, comment);
}

bool ufm::WriteToStream( const SdfSpecHandle& spec, std::ostream& out, size_t indent) const
{
    return SdfFileFormat::FindById(ufmTokens->Id)->WriteToStream(spec, out, indent);
}

void ufm::ComposeFieldsForFileFormatArguments(
    const std::string& assetPath,
    const pxr::PcpDynamicFileFormatContext& context,
    pxr::SdfFileFormat::FileFormatArguments* args,
    pxr::VtValue* contextDependencyData) const
{
    pxr::SdfFileFormat::FileFormatArguments outArgs;
    pxr::VtValue val;
    if (context.ComposeValue(ufmTokens->Params, &val) && val.IsHolding<VtDictionary>())
    {
        const pxr::VtDictionary& dict = val.UncheckedGet<pxr::VtDictionary>();
        // extra args here
    }
    * args = outArgs;
}

bool ufm::_ShouldSkipAnonymousReload() const
{
    return false;
}

bool ufm::_ShouldReadAnonymousLayers() const
{
    return true;
}