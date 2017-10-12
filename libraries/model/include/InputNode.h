////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Learning Library (ELL)
//  File:     InputNode.h (model)
//  Authors:  Chuck Jacobs
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "CompilableNode.h"
#include "InputNodeBase.h"
#include "InputPort.h"
#include "ModelTransformer.h"
#include "Node.h"
#include "OutputPort.h"

// math
#include "TensorShape.h"

// utilities
#include "IArchivable.h"
#include "TypeName.h"

#include <memory>
#include <string>
#include <vector>

namespace ell
{
/// <summary> model namespace </summary>
namespace model
{
    using InputShape = ell::math::TensorShape;

    /// <summary> A node that represents an input to the system. </summary>
    template<typename ValueType>
    class InputNode : public InputNodeBase
    {
    public:
        /// @name Input and Output Ports
        /// @{
        static constexpr const char* outputPortName = "output";
        const model::OutputPort<ValueType>& output = _output;
        /// @}

        /// <summary> Constructor </summary>
        InputNode();

        /// <summary> Constructor </summary>
        ///
        /// <param name="size"> The input size </param>
        InputNode(size_t size);

        /// <summary> Constructor </summary>
        ///
        /// <param name="size"> The input shape </param>
        InputNode(InputShape shape);

        /// <summary> Sets the value output by this node </summary>
        ///
        /// <param name="inputValues"> The value for this node to output </param>
        void SetInput(ValueType inputValue);

        /// <summary> Sets the value output by this node </summary>
        ///
        /// <param name="inputValues"> The values for this node to output </param>
        void SetInput(std::vector<ValueType> inputValues);

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        static std::string GetTypeName() { return utilities::GetCompositeTypeName<ValueType>("InputNode"); }

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        virtual std::string GetRuntimeTypeName() const override { return GetTypeName(); }

        /// <summary> Makes a copy of this node in the model being constructed by the transformer </summary>
        virtual void Copy(ModelTransformer& transformer) const override;

        /// <summary></summary>
        size_t Size() const { return _output.Size(); }

    protected:
        virtual void Compute() const override;
        virtual void Compile(IRMapCompiler& compiler, emitters::IRFunctionEmitter& function) override;
        virtual void WriteToArchive(utilities::Archiver& archiver) const override;
        virtual void ReadFromArchive(utilities::Unarchiver& archiver) override;
    private:
        std::vector<ValueType> _inputValues;
        OutputPort<ValueType> _output;
    };
}
}

#include "../tcc/InputNode.tcc"
