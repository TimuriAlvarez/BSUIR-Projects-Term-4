#pragma once

#include "../tfilesystem.h"

TDir T_CLASS(TDir, close)(TDir const dir, const TBool terminate);
TBool T_CLASS(TDir, exists)(TMessage dir_path);
TDir T_CLASS(TDir, open)(TMessage dir_path, const TBool terminate);
void T_CLASS(TDir, create)(TMessage dir_path, const mode_t dir_mode, const TBool terminate);
void T_CLASS(TDir, remove)(TMessage dir_path, const TBool terminate);
void T_CLASS(TDir, erase)(TMessage dir_path, const TBool terminate);
void T_CLASS(TDir, touch)(TMessage dir_path, const mode_t dir_mode);
void T_CLASS(TDir, untouch)(TMessage dir_path);
void T_CLASS(TDir, copy)(TMessage old_dir_path, TMessage new_dir_path, const TBool terminate);
void T_CLASS(TDir, move)(TMessage old_dir_path, TMessage new_dir_path, const TBool terminate);
