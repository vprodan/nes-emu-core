#pragma once
#include <cstdint>
#include <map>
#include <memory>
#include "cpu/opcode/handlers/OpcodeHandler.hpp"
#include "cpu/opcode/addressing/AddressingModeRepository.cpp"
#include "cpu/opcode/handlers/AddOpcodeHandler.cpp"
#include "cpu/opcode/handlers/AndOpcodeHandler.cpp"
#include "cpu/opcode/handlers/BranchStatusOpcodeHandler.cpp"
#include "cpu/opcode/handlers/BreakOpcodeHandler.cpp"
#include "cpu/opcode/handlers/CompareOpcodeHandler.cpp"
#include "cpu/opcode/handlers/DecrementOpcodeHandler.cpp"
#include "cpu/opcode/handlers/IncrementOpcodeHandler.cpp"
#include "cpu/opcode/handlers/JumpOpcodeHandler.cpp"
#include "cpu/opcode/handlers/JumpToSubroutineOpcodeHandler.cpp"
#include "cpu/opcode/handlers/LoadRegisterOpcodeHandler.cpp"
#include "cpu/opcode/handlers/StoreRegisterOpcodeHandler.cpp"
#include "cpu/opcode/handlers/NoopOpcodeHandler.cpp"
#include "cpu/opcode/handlers/OrOpcodeHandler.cpp"
#include "cpu/opcode/handlers/PullAccumulatorOpcodeHandler.cpp"
#include "cpu/opcode/handlers/PullStatusOpcodeHandler.cpp"
#include "cpu/opcode/handlers/PushAccumulatorOpcodeHandler.cpp"
#include "cpu/opcode/handlers/PushStatusOpcodeHandler.cpp"
#include "cpu/opcode/handlers/ReturnFromInterruptOpcodeHandler.cpp"
#include "cpu/opcode/handlers/ReturnFromSubroutineOpcodeHandler.cpp"
#include "cpu/opcode/handlers/RotateLeftOpcodeHandler.cpp"
#include "cpu/opcode/handlers/RotateRightOpcodeHandler.cpp"
#include "cpu/opcode/handlers/ShiftLeftOpcodeHandler.cpp"
#include "cpu/opcode/handlers/ShiftRightOpcodeHandler.cpp"
#include "cpu/opcode/handlers/StatusFlagOpcodeHandler.cpp"
#include "cpu/opcode/handlers/SubstractOpcodeHandler.cpp"
#include "cpu/opcode/handlers/TestOpcodeHandler.cpp"
#include "cpu/opcode/handlers/TransferRegisterOpcodeHandler.cpp"
#include "cpu/opcode/handlers/XorOpcodeHandler.cpp"
#include "cpu/register/StatusRegister.cpp"
using namespace std;

class OpcodeHandlerRepository
{
public:
    static OpcodeHandlerRepository &getInstance()
    {
        static OpcodeHandlerRepository instance;

        return instance;
    }

    OpcodeHandler *get(uint8_t opcode)
    {
        return repo[opcode].get();
    }

private:
    OpcodeHandlerRepository()
    {
        auto &addrModeRepo = AddressingModeRepository::getInstance();
        auto abs = addrModeRepo.get(Absolute);
        auto absX = addrModeRepo.get(AbsoluteX);
        auto absY = addrModeRepo.get(AbsoluteY);
        auto imm = addrModeRepo.get(Immediate);
        auto ind = addrModeRepo.get(Indirect);
        auto indX = addrModeRepo.get(IndirectX);
        auto indY = addrModeRepo.get(IndirectY);
        auto rel = addrModeRepo.get(Relative);
        auto zp = addrModeRepo.get(ZeroPage);
        auto zpX = addrModeRepo.get(ZeroPageX);
        auto zpY = addrModeRepo.get(ZeroPageY);

// https://www.nesdev.org/wiki/Instruction_reference

// #region Access
        // LDA
        repo[0xA9] = make_unique<LoadRegisterOpcodeHandler>(2, imm, &CPU::A);
        repo[0xA5] = make_unique<LoadRegisterOpcodeHandler>(3, zp, &CPU::A);
        repo[0xB5] = make_unique<LoadRegisterOpcodeHandler>(4, zpX, &CPU::A);
        repo[0xAD] = make_unique<LoadRegisterOpcodeHandler>(4, abs, &CPU::A);
        repo[0xBD] = make_unique<LoadRegisterOpcodeHandler>(4, absX, &CPU::A);
        repo[0xB9] = make_unique<LoadRegisterOpcodeHandler>(4, absY, &CPU::A);
        repo[0xA1] = make_unique<LoadRegisterOpcodeHandler>(6, indX, &CPU::A);
        repo[0xB1] = make_unique<LoadRegisterOpcodeHandler>(5, indY, &CPU::A);

        // STA
        repo[0x85] = make_unique<StoreRegisterOpcodeHandler>(3, zp, &CPU::A);
        repo[0x95] = make_unique<StoreRegisterOpcodeHandler>(4, zpX, &CPU::A);
        repo[0x8D] = make_unique<StoreRegisterOpcodeHandler>(4, abs, &CPU::A);
        repo[0x9D] = make_unique<StoreRegisterOpcodeHandler>(5, absX, &CPU::A);
        repo[0x99] = make_unique<StoreRegisterOpcodeHandler>(5, absY, &CPU::A);
        repo[0x81] = make_unique<StoreRegisterOpcodeHandler>(6, indX, &CPU::A);
        repo[0x91] = make_unique<StoreRegisterOpcodeHandler>(6, indY, &CPU::A);

        // LDX
        repo[0xA2] = make_unique<LoadRegisterOpcodeHandler>(2, imm, &CPU::X);
        repo[0xA6] = make_unique<LoadRegisterOpcodeHandler>(3, zp, &CPU::X);
        repo[0xB6] = make_unique<LoadRegisterOpcodeHandler>(4, zpY, &CPU::X);
        repo[0xAE] = make_unique<LoadRegisterOpcodeHandler>(4, abs, &CPU::X);
        repo[0xBE] = make_unique<LoadRegisterOpcodeHandler>(4, absY, &CPU::X);

        // STX
        repo[0x86] = make_unique<StoreRegisterOpcodeHandler>(3, zp, &CPU::X);
        repo[0x96] = make_unique<StoreRegisterOpcodeHandler>(4, zpY, &CPU::X);
        repo[0x8E] = make_unique<StoreRegisterOpcodeHandler>(4, abs, &CPU::X);

        // LDY
        repo[0xA0] = make_unique<LoadRegisterOpcodeHandler>(2, imm, &CPU::Y);
        repo[0xA4] = make_unique<LoadRegisterOpcodeHandler>(3, zp, &CPU::Y);
        repo[0xB4] = make_unique<LoadRegisterOpcodeHandler>(4, zpX, &CPU::Y);
        repo[0xAC] = make_unique<LoadRegisterOpcodeHandler>(4, abs, &CPU::Y);
        repo[0xBC] = make_unique<LoadRegisterOpcodeHandler>(4, absX, &CPU::Y);

        // STY
        repo[0x84] = make_unique<StoreRegisterOpcodeHandler>(3, zp, &CPU::Y);
        repo[0x94] = make_unique<StoreRegisterOpcodeHandler>(4, zpX, &CPU::Y);
        repo[0x8C] = make_unique<StoreRegisterOpcodeHandler>(4, abs, &CPU::Y);
// #endregion

// #region Transfer
        // TAX
        repo[0xAA] = make_unique<TransferRegisterOpcodeHandler>(2, &CPU::A, &CPU::X);

        // TXA
        repo[0x8A] = make_unique<TransferRegisterOpcodeHandler>(2, &CPU::X, &CPU::A);

        // TAY
        repo[0xA8] = make_unique<TransferRegisterOpcodeHandler>(2, &CPU::A, &CPU::Y);

        // TYA
        repo[0x98] = make_unique<TransferRegisterOpcodeHandler>(2, &CPU::Y, &CPU::A);
// #endregion

// #region Arithmetic
        // ADC
        repo[0x69] = make_unique<AddOpcodeHandler>(2, imm);
        repo[0x65] = make_unique<AddOpcodeHandler>(3, zp);
        repo[0x75] = make_unique<AddOpcodeHandler>(4, zpX);
        repo[0x6D] = make_unique<AddOpcodeHandler>(4, abs);
        repo[0x7D] = make_unique<AddOpcodeHandler>(4, absX);
        repo[0x79] = make_unique<AddOpcodeHandler>(4, absY);
        repo[0x61] = make_unique<AddOpcodeHandler>(6, indX);
        repo[0x71] = make_unique<AddOpcodeHandler>(5, indY);

        // SBC
        repo[0xE9] = make_unique<SubstractOpcodeHandler>(2, imm);
        repo[0xE5] = make_unique<SubstractOpcodeHandler>(3, zp);
        repo[0xF5] = make_unique<SubstractOpcodeHandler>(4, zpX);
        repo[0xED] = make_unique<SubstractOpcodeHandler>(4, abs);
        repo[0xFD] = make_unique<SubstractOpcodeHandler>(4, absX);
        repo[0xF9] = make_unique<SubstractOpcodeHandler>(4, absY);
        repo[0xE1] = make_unique<SubstractOpcodeHandler>(6, indX);
        repo[0xF1] = make_unique<SubstractOpcodeHandler>(5, indY);

        // INC
        repo[0xE6] = make_unique<IncrementOpcodeHandler>(5, zp);
        repo[0xF6] = make_unique<IncrementOpcodeHandler>(6, zpX);
        repo[0xEE] = make_unique<IncrementOpcodeHandler>(6, abs);
        repo[0xFE] = make_unique<IncrementOpcodeHandler>(7, absX);

        // DEC
        repo[0xC6] = make_unique<DecrementOpcodeHandler>(5, zp);
        repo[0xD6] = make_unique<DecrementOpcodeHandler>(6, zpX);
        repo[0xCE] = make_unique<DecrementOpcodeHandler>(6, abs);
        repo[0xDE] = make_unique<DecrementOpcodeHandler>(7, absX);

        // INX
        repo[0xE8] = make_unique<IncrementOpcodeHandler>(2, &CPU::X);

        // DEX
        repo[0xCA] = make_unique<DecrementOpcodeHandler>(2, &CPU::X);
        
        // INY
        repo[0xC8] = make_unique<IncrementOpcodeHandler>(2, &CPU::Y);

        // DEY
        repo[0x88] = make_unique<DecrementOpcodeHandler>(2, &CPU::Y);
// #endregion

// #region Shift
        // ASL
        repo[0x0A] = make_unique<ShiftLeftOpcodeHandler>(2, &CPU::A);
        repo[0x06] = make_unique<ShiftLeftOpcodeHandler>(5, zp);
        repo[0x16] = make_unique<ShiftLeftOpcodeHandler>(6, zpX);
        repo[0x0E] = make_unique<ShiftLeftOpcodeHandler>(6, abs);
        repo[0x1E] = make_unique<ShiftLeftOpcodeHandler>(7, absX);

        // LSR
        repo[0x4A] = make_unique<ShiftRightOpcodeHandler>(2, &CPU::A);
        repo[0x46] = make_unique<ShiftRightOpcodeHandler>(5, zp);
        repo[0x56] = make_unique<ShiftRightOpcodeHandler>(6, zpX);
        repo[0x4E] = make_unique<ShiftRightOpcodeHandler>(6, abs);
        repo[0x5E] = make_unique<ShiftRightOpcodeHandler>(7, absX);

        // ROL
        repo[0x2A] = make_unique<RotateLeftOpcodeHandler>(2, &CPU::A);
        repo[0x26] = make_unique<RotateLeftOpcodeHandler>(5, zp);
        repo[0x36] = make_unique<RotateLeftOpcodeHandler>(6, zpX);
        repo[0x2E] = make_unique<RotateLeftOpcodeHandler>(6, abs);
        repo[0x3E] = make_unique<RotateLeftOpcodeHandler>(7, absX);

        // ROR
        repo[0x6A] = make_unique<RotateRightOpcodeHandler>(2, &CPU::A);
        repo[0x66] = make_unique<RotateRightOpcodeHandler>(5, zp);
        repo[0x76] = make_unique<RotateRightOpcodeHandler>(6, zpX);
        repo[0x6E] = make_unique<RotateRightOpcodeHandler>(6, abs);
        repo[0x7E] = make_unique<RotateRightOpcodeHandler>(7, absX);
// #endregion

// #region Bitwise
        // AND
        repo[0x29] = make_unique<AndOpcodeHandler>(2, imm);
        repo[0x25] = make_unique<AndOpcodeHandler>(3, zp);
        repo[0x35] = make_unique<AndOpcodeHandler>(4, zpX);
        repo[0x2D] = make_unique<AndOpcodeHandler>(4, abs);
        repo[0x3D] = make_unique<AndOpcodeHandler>(4, absX);
        repo[0x39] = make_unique<AndOpcodeHandler>(4, absY);
        repo[0x21] = make_unique<AndOpcodeHandler>(6, indX);
        repo[0x31] = make_unique<AndOpcodeHandler>(5, indY);

        // ORA
        repo[0x09] = make_unique<OrOpcodeHandler>(2, imm);
        repo[0x05] = make_unique<OrOpcodeHandler>(3, zp);
        repo[0x15] = make_unique<OrOpcodeHandler>(4, zpX);
        repo[0x0D] = make_unique<OrOpcodeHandler>(4, abs);
        repo[0x1D] = make_unique<OrOpcodeHandler>(4, absX);
        repo[0x19] = make_unique<OrOpcodeHandler>(4, absY);
        repo[0x01] = make_unique<OrOpcodeHandler>(6, indX);
        repo[0x11] = make_unique<OrOpcodeHandler>(5, indY);

        // EOR
        repo[0x49] = make_unique<XorOpcodeHandler>(2, imm);
        repo[0x45] = make_unique<XorOpcodeHandler>(3, zp);
        repo[0x55] = make_unique<XorOpcodeHandler>(4, zpX);
        repo[0x4D] = make_unique<XorOpcodeHandler>(4, abs);
        repo[0x5D] = make_unique<XorOpcodeHandler>(4, absX);
        repo[0x59] = make_unique<XorOpcodeHandler>(4, absY);
        repo[0x41] = make_unique<XorOpcodeHandler>(6, indX);
        repo[0x51] = make_unique<XorOpcodeHandler>(5, indY);

        // BIT
        repo[0x24] = make_unique<TestOpcodeHandler>(3, zp);
        repo[0x2C] = make_unique<TestOpcodeHandler>(4, abs);
// #endregion

// #region Compare
        // CMP
        repo[0xC9] = make_unique<CompareOpcodeHandler>(2, imm, &CPU::A);
        repo[0xC5] = make_unique<CompareOpcodeHandler>(3, zp, &CPU::A);
        repo[0xD5] = make_unique<CompareOpcodeHandler>(4, zpX, &CPU::A);
        repo[0xCD] = make_unique<CompareOpcodeHandler>(4, abs, &CPU::A);
        repo[0xDD] = make_unique<CompareOpcodeHandler>(4, absX, &CPU::A);;
        repo[0xD9] = make_unique<CompareOpcodeHandler>(4, absY, &CPU::A);;
        repo[0xC1] = make_unique<CompareOpcodeHandler>(6, indX, &CPU::A);;
        repo[0xD1] = make_unique<CompareOpcodeHandler>(5, indY, &CPU::A);;

        // CPX
        repo[0xE0] = make_unique<CompareOpcodeHandler>(2, imm, &CPU::X);
        repo[0xE4] = make_unique<CompareOpcodeHandler>(3, zp, &CPU::X);
        repo[0xEC] = make_unique<CompareOpcodeHandler>(4, abs, &CPU::X);

        // CPY
        repo[0xC0] = make_unique<CompareOpcodeHandler>(2, imm, &CPU::Y);
        repo[0xC4] = make_unique<CompareOpcodeHandler>(3, zp, &CPU::Y);
        repo[0xCC] = make_unique<CompareOpcodeHandler>(4, abs, &CPU::Y);
// #endregion

// #region Branch
        // BCC
        repo[0x90] = make_unique<BranchStatusOpcodeHandler>(2, rel, Carry, false);

        // BCS
        repo[0xB0] = make_unique<BranchStatusOpcodeHandler>(2, rel, Carry, true);

        // BEQ
        repo[0xF0] = make_unique<BranchStatusOpcodeHandler>(2, rel, Zero, true);

        // BNE
        repo[0xD0] = make_unique<BranchStatusOpcodeHandler>(2, rel, Zero, false);

        // BPL
        repo[0x10] = make_unique<BranchStatusOpcodeHandler>(2, rel, Negative, false);
        
        // BMI
        repo[0x30] = make_unique<BranchStatusOpcodeHandler>(2, rel, Negative, true);

        // BVC
        repo[0x50] = make_unique<BranchStatusOpcodeHandler>(2, rel, Overflow, false);

        // BVS
        repo[0x70] = make_unique<BranchStatusOpcodeHandler>(2, rel, Overflow, true);
// #endregion

// #region Jump
        // JMP
        repo[0x4C] = make_unique<JumpOpcodeHandler>(3, abs);
        repo[0x6C] = make_unique<JumpOpcodeHandler>(5, ind);

        // JSR
        repo[0x20] = make_unique<JumpToSubroutineOpcodeHandler>(6);

        // RTS
        repo[0x60] = make_unique<ReturnFromSubroutineOpcodeHandler>(6);

        // BRK
        repo[0x00] = make_unique<BreakOpcodeHandler>(7);

        // RTI
        repo[0x40] = make_unique<ReturnFromInterruptOpcodeHandler>(6);
// #endregion

// #region Stack
        // PHA
        repo[0x48] = make_unique<PushAccumulatorOpcodeHandler>(3);

        // PLA
        repo[0x68] = make_unique<PullAccumulatorOpcodeHandler>(4);

        // PHP
        repo[0x08] = make_unique<PushStatusOpcodeHandler>(3);

        // PLP
        repo[0x28] = make_unique<PullStatusOpcodeHandler>(4);

        // TXS
        repo[0x9A] = make_unique<TransferRegisterOpcodeHandler>(2, &CPU::X, reinterpret_cast<Register<uint8_t> CPU::*>(&CPU::S));

        // TSX
        repo[0xBA] = make_unique<TransferRegisterOpcodeHandler>(2, reinterpret_cast<Register<uint8_t> CPU::*>(&CPU::S), &CPU::X);
// #endregion

// #region Flags
        // CLC
        repo[0x18] = make_unique<StatusFlagOpcodeHandler>(2, Carry, false);

        // SEC
        repo[0x38] = make_unique<StatusFlagOpcodeHandler>(2, Carry, true);

        // CLI
        repo[0x58] = make_unique<StatusFlagOpcodeHandler>(2, InterruptDisable, false);

        // SEI
        repo[0x78] = make_unique<StatusFlagOpcodeHandler>(2, InterruptDisable, true);

        // CLD
        repo[0xD8] = make_unique<StatusFlagOpcodeHandler>(2, Decimal, false);

        // SED
        repo[0xF8] = make_unique<StatusFlagOpcodeHandler>(2, Decimal, true);

        // CLV
        repo[0xB8] = make_unique<StatusFlagOpcodeHandler>(2, Overflow, false);
// #endregion

// #region Other
        // NOP
        repo[0xEA] = make_unique<NoopOpcodeHandler>(2);
// #endregion
    }

    map<uint8_t, unique_ptr<OpcodeHandler>> repo;

    OpcodeHandlerRepository(const OpcodeHandlerRepository &) = delete;
    OpcodeHandlerRepository &operator=(const OpcodeHandlerRepository &) = delete;
};