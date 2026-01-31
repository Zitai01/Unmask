ROOT = path.getabsolute("./").."/"
include("premake/premake.utils.lua")
workspace "nvigi"
include("premake/premake.shared_config.lua")
include("premake/premake.shared_plugin.lua")
include("premake/premake.cuda_utils.lua")
include("source/samples/nvigi.basic/premake.lua")
include("source/samples/nvigi.pipeline/premake.lua")
include("source/samples/nvigi.rag/premake.lua")
