#include "STM32HALModule.h"
#include "interop/DekiPlugin.h"
#include "DekiModuleFeatureMeta.h"
#include "reflection/ComponentRegistry.h"
#include "reflection/ComponentFactory.h"

// Direct backend registration for STM32 hardware
#if defined(DEKI_STM32)
#include "platforms/stm32/STM32TimeProvider.h"
#include "DekiTime.h"

namespace
{
struct STM32BackendInit {
    STM32BackendInit() {
        DekiTime::SetTimeProvider(std::make_unique<STM32TimeProvider>());
    }
};
static STM32BackendInit s_stm32_init;
}

#include "DekiMain.h"
int main(void) { return DekiMain(); }

#endif // DEKI_STM32

#ifdef DEKI_EDITOR

// Auto-generated registration helpers
extern void DekiSTM32HAL_RegisterComponents();
extern int DekiSTM32HAL_GetAutoComponentCount();
extern const DekiComponentMeta* DekiSTM32HAL_GetAutoComponentMeta(int index);

// Track if already registered to avoid duplicates
static bool s_STM32HALRegistered = false;

extern "C" {

DEKI_STM32_HAL_API int DekiSTM32HAL_EnsureRegistered(void)
{
    if (s_STM32HALRegistered)
        return DekiSTM32HAL_GetAutoComponentCount();
    s_STM32HALRegistered = true;

    DekiSTM32HAL_RegisterComponents();

    return DekiSTM32HAL_GetAutoComponentCount();
}

// =============================================================================
// Plugin metadata (for dynamic loading compatibility)
// =============================================================================

DEKI_PLUGIN_API const char* DekiPlugin_GetName(void)
{
    return "Deki STM32 HAL Module";
}

DEKI_PLUGIN_API const char* DekiPlugin_GetVersion(void)
{
#ifdef DEKI_MODULE_VERSION
    return DEKI_MODULE_VERSION;
#else
    return "0.0.0-dev";
#endif
}

DEKI_PLUGIN_API const char* DekiPlugin_GetReflectionJson(void)
{
    return "{}";
}

DEKI_PLUGIN_API int DekiPlugin_Init(void)
{
    return 0;
}

DEKI_PLUGIN_API void DekiPlugin_Shutdown(void)
{
    s_STM32HALRegistered = false;
}

DEKI_PLUGIN_API int DekiPlugin_GetComponentCount(void)
{
    return DekiSTM32HAL_GetAutoComponentCount();
}

DEKI_PLUGIN_API const DekiComponentMeta* DekiPlugin_GetComponentMeta(int index)
{
    return DekiSTM32HAL_GetAutoComponentMeta(index);
}

DEKI_PLUGIN_API void DekiPlugin_RegisterComponents(void)
{
    DekiSTM32HAL_EnsureRegistered();
}

// =============================================================================
// Module Feature API
// =============================================================================

DEKI_PLUGIN_API int DekiPlugin_GetFeatureCount(void)
{
    return 0;
}

DEKI_PLUGIN_API const DekiModuleFeatureInfo* DekiPlugin_GetFeature(int index)
{
    (void)index;
    return nullptr;
}

// =============================================================================
// Module-specific feature API
// =============================================================================

DEKI_STM32_HAL_API const char* DekiSTM32HAL_GetName(void)
{
    return "STM32 HAL";
}

DEKI_STM32_HAL_API int DekiSTM32HAL_GetFeatureCount(void)
{
    return 0;
}

DEKI_STM32_HAL_API const DekiModuleFeatureInfo* DekiSTM32HAL_GetFeature(int index)
{
    (void)index;
    return nullptr;
}

} // extern "C"

#else // !DEKI_EDITOR - Runtime registration

// For runtime builds, component registration happens via static initializers

#endif // DEKI_EDITOR
