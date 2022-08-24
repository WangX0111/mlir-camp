'''
Author: WangX wangchenhao006@126.com
Date: 2022-08-22 14:43:17
LastEditors: WangX wangchenhao006@126.com
LastEditTime: 2022-08-24 14:54:15
FilePath: /toyalone/python/mlir_standalone/dialects/standalone.py
Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
'''
#  Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
#  See https://llvm.org/LICENSE.txt for license information.
#  SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

from ._standalone_ops_gen import *
from .._mlir_libs._standaloneDialects.standalone import *
