#pragma once

// @generated by torchgen/gen.py from Function.h

#include <ATen/Context.h>
#include <ATen/DeviceGuard.h>
#include <ATen/TensorUtils.h>
#include <ATen/TracerMode.h>
#include <ATen/core/Generator.h>
#include <ATen/core/Reduction.h>
#include <ATen/core/Tensor.h>
#include <c10/core/Scalar.h>
#include <c10/core/Storage.h>
#include <c10/core/TensorOptions.h>
#include <c10/util/Deprecated.h>
#include <c10/util/Optional.h>



#include <ATen/ops/slice_ops.h>

namespace at {


// aten::slice.Tensor(Tensor(a) self, int dim=0, SymInt? start=None, SymInt? end=None, SymInt step=1) -> Tensor(a)
inline at::Tensor slice(const at::Tensor & self, int64_t dim=0, c10::optional<int64_t> start=c10::nullopt, c10::optional<int64_t> end=c10::nullopt, int64_t step=1) {
    return at::_ops::slice_Tensor::call(self, dim, start.has_value() ? c10::make_optional(c10::SymInt(*start)) : c10::nullopt, end.has_value() ? c10::make_optional(c10::SymInt(*end)) : c10::nullopt, step);
}

// aten::slice.Tensor(Tensor(a) self, int dim=0, SymInt? start=None, SymInt? end=None, SymInt step=1) -> Tensor(a)
inline at::Tensor slice_symint(const at::Tensor & self, int64_t dim=0, c10::optional<c10::SymInt> start=c10::nullopt, c10::optional<c10::SymInt> end=c10::nullopt, c10::SymInt step=1) {
    return at::_ops::slice_Tensor::call(self, dim, start, end, step);
}

}