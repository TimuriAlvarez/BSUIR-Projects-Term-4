#pragma once

// ReSharper disable CppClangTidyClangDiagnosticInvalidSourceEncoding
// ReSharper disable StringLiteralTypo
// ReSharper disable CommentTypo
// ReSharper disable CppClangTidyConcurrencyMtUnsafe
#include "../../../Tlib Library C/Tlib Library C/tlib.h"
#include "../../../Tlib Library C/Tlib Library C/tcontainer/tstring.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#ifdef _WIN32
// ReSharper disable once CppInconsistentNaming
#include "../../../Tlib Library C/Tlib Library C/tlinux/sys/types.h"
#include "../../../Tlib Library C/Tlib Library C/tlinux/sys/wait.h"
#include "../../../Tlib Library C/Tlib Library C/tlinux/unistd.h"
#else
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#endif
