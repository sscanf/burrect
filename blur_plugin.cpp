#include "blur_plugin.h"
#include "blur.h"

#include <qqml.h>

void BlurPlugin::registerTypes(const char *uri)
{
    // @uri com.zitro.zone
    qmlRegisterType<blur>(uri, 1, 0, "Blur");
}

