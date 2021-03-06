.rdata
glabel D_80996060
    .asciz "bank_ID = %d\n"
    .balign 4

glabel D_80996070
    .asciz "status = %d\n"
    .balign 4

.late_rodata
glabel jtbl_809960A8
.word L80994D4C
.word L80994E88
.word L80994E88
.word L80994E88
.word L80994E88
glabel D_809960BC
 .word 0xBF19999A

.text
glabel DoorKiller_Init
/* 00000 80994C50 27BDFFA8 */  addiu   $sp, $sp, 0xFFA8           ## $sp = FFFFFFA8
/* 00004 80994C54 AFB10028 */  sw      $s1, 0x0028($sp)
/* 00008 80994C58 3C010001 */  lui     $at, 0x0001                ## $at = 00010000
/* 0000C 80994C5C AFB50038 */  sw      $s5, 0x0038($sp)
/* 00010 80994C60 AFB40034 */  sw      $s4, 0x0034($sp)
/* 00014 80994C64 AFB2002C */  sw      $s2, 0x002C($sp)
/* 00018 80994C68 AFB00024 */  sw      $s0, 0x0024($sp)
/* 0001C 80994C6C 342117A4 */  ori     $at, $at, 0x17A4           ## $at = 000117A4
/* 00020 80994C70 3C118099 */  lui     $s1, %hi(D_80996010)       ## $s1 = 80990000
/* 00024 80994C74 00809025 */  or      $s2, $a0, $zero            ## $s2 = 00000000
/* 00028 80994C78 00A0A825 */  or      $s5, $a1, $zero            ## $s5 = 00000000
/* 0002C 80994C7C AFBF003C */  sw      $ra, 0x003C($sp)
/* 00030 80994C80 AFB30030 */  sw      $s3, 0x0030($sp)
/* 00034 80994C84 26316010 */  addiu   $s1, $s1, %lo(D_80996010)  ## $s1 = 80996010
/* 00038 80994C88 00A1A021 */  addu    $s4, $a1, $at
/* 0003C 80994C8C 00008025 */  or      $s0, $zero, $zero          ## $s0 = 00000000
.L80994C90:
/* 00040 80994C90 02802025 */  or      $a0, $s4, $zero            ## $a0 = 00000000
/* 00044 80994C94 0C02604B */  jal     Object_GetIndex
              ## ObjectIndex
/* 00048 80994C98 86250000 */  lh      $a1, 0x0000($s1)           ## 80996010
/* 0004C 80994C9C A250021D */  sb      $s0, 0x021D($s2)           ## 0000021D
/* 00050 80994CA0 26100001 */  addiu   $s0, $s0, 0x0001           ## $s0 = 00000001
/* 00054 80994CA4 26310008 */  addiu   $s1, $s1, 0x0008           ## $s1 = 80996018
/* 00058 80994CA8 0440FFF9 */  bltz    $v0, .L80994C90
/* 0005C 80994CAC 00409825 */  or      $s3, $v0, $zero            ## $s3 = 00000000
/* 00060 80994CB0 3C048099 */  lui     $a0, %hi(D_80996060)       ## $a0 = 80990000
/* 00064 80994CB4 24846060 */  addiu   $a0, $a0, %lo(D_80996060)  ## $a0 = 80996060
/* 00068 80994CB8 0C00084C */  jal     osSyncPrintf

/* 0006C 80994CBC 00402825 */  or      $a1, $v0, $zero            ## $a1 = 00000000
/* 00070 80994CC0 3C048099 */  lui     $a0, %hi(D_80996070)       ## $a0 = 80990000
/* 00074 80994CC4 24846070 */  addiu   $a0, $a0, %lo(D_80996070)  ## $a0 = 80996070
/* 00078 80994CC8 0C00084C */  jal     osSyncPrintf

/* 0007C 80994CCC 9245021D */  lbu     $a1, 0x021D($s2)           ## 0000021D
/* 00080 80994CD0 924E021D */  lbu     $t6, 0x021D($s2)           ## 0000021D
/* 00084 80994CD4 44800000 */  mtc1    $zero, $f0                 ## $f0 = 0.00
/* 00088 80994CD8 3C188099 */  lui     $t8, %hi(D_80996014)       ## $t8 = 80990000
/* 0008C 80994CDC 000E78C0 */  sll     $t7, $t6,  3
/* 00090 80994CE0 A253021C */  sb      $s3, 0x021C($s2)           ## 0000021C
/* 00094 80994CE4 030FC021 */  addu    $t8, $t8, $t7
/* 00098 80994CE8 8F186014 */  lw      $t8, %lo(D_80996014)($t8)
/* 0009C 80994CEC 44050000 */  mfc1    $a1, $f0
/* 000A0 80994CF0 44070000 */  mfc1    $a3, $f0
/* 000A4 80994CF4 264400B4 */  addiu   $a0, $s2, 0x00B4           ## $a0 = 000000B4
/* 000A8 80994CF8 00003025 */  or      $a2, $zero, $zero          ## $a2 = 00000000
/* 000AC 80994CFC 0C00AC78 */  jal     ActorShape_Init

/* 000B0 80994D00 AE580214 */  sw      $t8, 0x0214($s2)           ## 00000214
/* 000B4 80994D04 3C053C23 */  lui     $a1, 0x3C23                ## $a1 = 3C230000
/* 000B8 80994D08 34A5D70A */  ori     $a1, $a1, 0xD70A           ## $a1 = 3C23D70A
/* 000BC 80994D0C 0C00B58B */  jal     Actor_SetScale

/* 000C0 80994D10 02402025 */  or      $a0, $s2, $zero            ## $a0 = 00000000
/* 000C4 80994D14 8648001C */  lh      $t0, 0x001C($s2)           ## 0000001C
/* 000C8 80994D18 A640021A */  sh      $zero, 0x021A($s2)         ## 0000021A
/* 000CC 80994D1C A6400218 */  sh      $zero, 0x0218($s2)         ## 00000218
/* 000D0 80994D20 310900FF */  andi    $t1, $t0, 0x00FF           ## $t1 = 00000000
/* 000D4 80994D24 2D210005 */  sltiu   $at, $t1, 0x0005
/* 000D8 80994D28 A2400190 */  sb      $zero, 0x0190($s2)         ## 00000190
/* 000DC 80994D2C 102000A0 */  beq     $at, $zero, .L80994FB0
/* 000E0 80994D30 A2400191 */  sb      $zero, 0x0191($s2)         ## 00000191
/* 000E4 80994D34 00094880 */  sll     $t1, $t1,  2
/* 000E8 80994D38 3C018099 */  lui     $at, %hi(jtbl_809960A8)       ## $at = 80990000
/* 000EC 80994D3C 00290821 */  addu    $at, $at, $t1
/* 000F0 80994D40 8C2960A8 */  lw      $t1, %lo(jtbl_809960A8)($at)
/* 000F4 80994D44 01200008 */  jr      $t1
/* 000F8 80994D48 00000000 */  nop
glabel L80994D4C
/* 000FC 80994D4C 3C060600 */  lui     $a2, 0x0600                ## $a2 = 06000000
/* 00100 80994D50 26420192 */  addiu   $v0, $s2, 0x0192           ## $v0 = 00000192
/* 00104 80994D54 240A0009 */  addiu   $t2, $zero, 0x0009         ## $t2 = 00000009
/* 00108 80994D58 AFAA0018 */  sw      $t2, 0x0018($sp)
/* 0010C 80994D5C AFA20010 */  sw      $v0, 0x0010($sp)
/* 00110 80994D60 AFA20014 */  sw      $v0, 0x0014($sp)
/* 00114 80994D64 24C61BC8 */  addiu   $a2, $a2, 0x1BC8           ## $a2 = 06001BC8
/* 00118 80994D68 02A02025 */  or      $a0, $s5, $zero            ## $a0 = 00000000
/* 0011C 80994D6C 2645014C */  addiu   $a1, $s2, 0x014C           ## $a1 = 0000014C
/* 00120 80994D70 0C0291BE */  jal     SkelAnime_InitSV
/* 00124 80994D74 00003825 */  or      $a3, $zero, $zero          ## $a3 = 00000000
/* 00128 80994D78 3C0B8099 */  lui     $t3, %hi(func_80995D6C)    ## $t3 = 80990000
/* 0012C 80994D7C 256B5D6C */  addiu   $t3, $t3, %lo(func_80995D6C) ## $t3 = 80995D6C
/* 00130 80994D80 AE4B0280 */  sw      $t3, 0x0280($s2)           ## 00000280
/* 00134 80994D84 02402025 */  or      $a0, $s2, $zero            ## $a0 = 00000000
/* 00138 80994D88 0C26575B */  jal     func_80995D6C
/* 0013C 80994D8C 02A02825 */  or      $a1, $s5, $zero            ## $a1 = 00000000
/* 00140 80994D90 240C4000 */  addiu   $t4, $zero, 0x4000         ## $t4 = 00004000
/* 00144 80994D94 A64C019C */  sh      $t4, 0x019C($s2)           ## 0000019C
/* 00148 80994D98 864D019C */  lh      $t5, 0x019C($s2)           ## 0000019C
/* 0014C 80994D9C 265001C8 */  addiu   $s0, $s2, 0x01C8           ## $s0 = 000001C8
/* 00150 80994DA0 02002825 */  or      $a1, $s0, $zero            ## $a1 = 000001C8
/* 00154 80994DA4 02A02025 */  or      $a0, $s5, $zero            ## $a0 = 00000000
/* 00158 80994DA8 0C0170D9 */  jal     Collider_InitCylinder

/* 0015C 80994DAC A64D0198 */  sh      $t5, 0x0198($s2)           ## 00000198
/* 00160 80994DB0 3C078099 */  lui     $a3, %hi(D_80995FB0)       ## $a3 = 80990000
/* 00164 80994DB4 24E75FB0 */  addiu   $a3, $a3, %lo(D_80995FB0)  ## $a3 = 80995FB0
/* 00168 80994DB8 02A02025 */  or      $a0, $s5, $zero            ## $a0 = 00000000
/* 0016C 80994DBC 02002825 */  or      $a1, $s0, $zero            ## $a1 = 000001C8
/* 00170 80994DC0 0C01712B */  jal     Collider_SetCylinder

/* 00174 80994DC4 02403025 */  or      $a2, $s2, $zero            ## $a2 = 00000000
/* 00178 80994DC8 26500220 */  addiu   $s0, $s2, 0x0220           ## $s0 = 00000220
/* 0017C 80994DCC 02002825 */  or      $a1, $s0, $zero            ## $a1 = 00000220
/* 00180 80994DD0 0C016EFE */  jal     Collider_InitJntSph
/* 00184 80994DD4 02A02025 */  or      $a0, $s5, $zero            ## $a0 = 00000000
/* 00188 80994DD8 3C078099 */  lui     $a3, %hi(D_80996000)       ## $a3 = 80990000
/* 0018C 80994DDC 264E0240 */  addiu   $t6, $s2, 0x0240           ## $t6 = 00000240
/* 00190 80994DE0 AFAE0010 */  sw      $t6, 0x0010($sp)
/* 00194 80994DE4 24E76000 */  addiu   $a3, $a3, %lo(D_80996000)  ## $a3 = 80996000
/* 00198 80994DE8 02A02025 */  or      $a0, $s5, $zero            ## $a0 = 00000000
/* 0019C 80994DEC 02002825 */  or      $a1, $s0, $zero            ## $a1 = 00000220
/* 001A0 80994DF0 0C017014 */  jal     Collider_SetJntSph
/* 001A4 80994DF4 02403025 */  or      $a2, $s2, $zero            ## $a2 = 00000000
/* 001A8 80994DF8 8E58023C */  lw      $t8, 0x023C($s2)           ## 0000023C
/* 001AC 80994DFC 240F0050 */  addiu   $t7, $zero, 0x0050         ## $t7 = 00000050
/* 001B0 80994E00 2401003F */  addiu   $at, $zero, 0x003F         ## $at = 0000003F
/* 001B4 80994E04 A70F0036 */  sh      $t7, 0x0036($t8)           ## 00000036
/* 001B8 80994E08 C6440024 */  lwc1    $f4, 0x0024($s2)           ## 00000024
/* 001BC 80994E0C 8E49023C */  lw      $t1, 0x023C($s2)           ## 0000023C
/* 001C0 80994E10 4600218D */  trunc.w.s $f6, $f4
/* 001C4 80994E14 44083000 */  mfc1    $t0, $f6
/* 001C8 80994E18 00000000 */  nop
/* 001CC 80994E1C A5280030 */  sh      $t0, 0x0030($t1)           ## 00000030
/* 001D0 80994E20 C6480028 */  lwc1    $f8, 0x0028($s2)           ## 00000028
/* 001D4 80994E24 8E4F023C */  lw      $t7, 0x023C($s2)           ## 0000023C
/* 001D8 80994E28 4600428D */  trunc.w.s $f10, $f8
/* 001DC 80994E2C 440D5000 */  mfc1    $t5, $f10
/* 001E0 80994E30 00000000 */  nop
/* 001E4 80994E34 25AE0032 */  addiu   $t6, $t5, 0x0032           ## $t6 = 00000032
/* 001E8 80994E38 A5EE0032 */  sh      $t6, 0x0032($t7)           ## 00000082
/* 001EC 80994E3C C650002C */  lwc1    $f16, 0x002C($s2)          ## 0000002C
/* 001F0 80994E40 8E48023C */  lw      $t0, 0x023C($s2)           ## 0000023C
/* 001F4 80994E44 4600848D */  trunc.w.s $f18, $f16
/* 001F8 80994E48 44199000 */  mfc1    $t9, $f18
/* 001FC 80994E4C 00000000 */  nop
/* 00200 80994E50 A5190034 */  sh      $t9, 0x0034($t0)           ## 00000034
/* 00204 80994E54 8645001C */  lh      $a1, 0x001C($s2)           ## 0000001C
/* 00208 80994E58 00052A03 */  sra     $a1, $a1,  8
/* 0020C 80994E5C 30A5003F */  andi    $a1, $a1, 0x003F           ## $a1 = 00000000
/* 00210 80994E60 50A10054 */  beql    $a1, $at, .L80994FB4
/* 00214 80994E64 8FBF003C */  lw      $ra, 0x003C($sp)
/* 00218 80994E68 0C00B2D0 */  jal     Flags_GetSwitch

/* 0021C 80994E6C 02A02025 */  or      $a0, $s5, $zero            ## $a0 = 00000000
/* 00220 80994E70 50400050 */  beql    $v0, $zero, .L80994FB4
/* 00224 80994E74 8FBF003C */  lw      $ra, 0x003C($sp)
/* 00228 80994E78 0C00B55C */  jal     Actor_Kill

/* 0022C 80994E7C 02402025 */  or      $a0, $s2, $zero            ## $a0 = 00000000
/* 00230 80994E80 1000004C */  beq     $zero, $zero, .L80994FB4
/* 00234 80994E84 8FBF003C */  lw      $ra, 0x003C($sp)
glabel L80994E88
/* 00238 80994E88 3C098099 */  lui     $t1, %hi(func_80995D6C)    ## $t1 = 80990000
/* 0023C 80994E8C 25295D6C */  addiu   $t1, $t1, %lo(func_80995D6C) ## $t1 = 80995D6C
/* 00240 80994E90 AE490280 */  sw      $t1, 0x0280($s2)           ## 00000280
/* 00244 80994E94 02402025 */  or      $a0, $s2, $zero            ## $a0 = 00000000
/* 00248 80994E98 0C26575B */  jal     func_80995D6C
/* 0024C 80994E9C 02A02825 */  or      $a1, $s5, $zero            ## $a1 = 00000000
/* 00250 80994EA0 3C018099 */  lui     $at, %hi(D_809960BC)       ## $at = 80990000
/* 00254 80994EA4 C42460BC */  lwc1    $f4, %lo(D_809960BC)($at)
/* 00258 80994EA8 3C01C0C0 */  lui     $at, 0xC0C0                ## $at = C0C00000
/* 0025C 80994EAC 44813000 */  mtc1    $at, $f6                   ## $f6 = -6.00
/* 00260 80994EB0 3C014100 */  lui     $at, 0x4100                ## $at = 41000000
/* 00264 80994EB4 44816000 */  mtc1    $at, $f12                  ## $f12 = 8.00
/* 00268 80994EB8 E644006C */  swc1    $f4, 0x006C($s2)           ## 0000006C
/* 0026C 80994EBC 0C00CFC8 */  jal     Math_Rand_CenteredFloat

/* 00270 80994EC0 E6460070 */  swc1    $f6, 0x0070($s2)           ## 00000070
/* 00274 80994EC4 3C014100 */  lui     $at, 0x4100                ## $at = 41000000
/* 00278 80994EC8 44816000 */  mtc1    $at, $f12                  ## $f12 = 8.00
/* 0027C 80994ECC 0C00CFBE */  jal     Math_Rand_ZeroFloat

/* 00280 80994ED0 E7A00050 */  swc1    $f0, 0x0050($sp)
/* 00284 80994ED4 E6400064 */  swc1    $f0, 0x0064($s2)           ## 00000064
/* 00288 80994ED8 0C01DE0D */  jal     Math_Coss
              ## coss?
/* 0028C 80994EDC 86440032 */  lh      $a0, 0x0032($s2)           ## 00000032
/* 00290 80994EE0 E7A00040 */  swc1    $f0, 0x0040($sp)
/* 00294 80994EE4 0C01DE1C */  jal     Math_Sins
              ## sins?
/* 00298 80994EE8 86440032 */  lh      $a0, 0x0032($s2)           ## 00000032
/* 0029C 80994EEC C7A80040 */  lwc1    $f8, 0x0040($sp)
/* 002A0 80994EF0 C7AA0050 */  lwc1    $f10, 0x0050($sp)
/* 002A4 80994EF4 C6520064 */  lwc1    $f18, 0x0064($s2)          ## 00000064
/* 002A8 80994EF8 86440032 */  lh      $a0, 0x0032($s2)           ## 00000032
/* 002AC 80994EFC 460A4402 */  mul.s   $f16, $f8, $f10
/* 002B0 80994F00 00000000 */  nop
/* 002B4 80994F04 46120102 */  mul.s   $f4, $f0, $f18
/* 002B8 80994F08 46102180 */  add.s   $f6, $f4, $f16
/* 002BC 80994F0C 0C01DE1C */  jal     Math_Sins
              ## sins?
/* 002C0 80994F10 E646005C */  swc1    $f6, 0x005C($s2)           ## 0000005C
/* 002C4 80994F14 E7A00040 */  swc1    $f0, 0x0040($sp)
/* 002C8 80994F18 0C01DE0D */  jal     Math_Coss
              ## coss?
/* 002CC 80994F1C 86440032 */  lh      $a0, 0x0032($s2)           ## 00000032
/* 002D0 80994F20 C7A80040 */  lwc1    $f8, 0x0040($sp)
/* 002D4 80994F24 C7B20050 */  lwc1    $f18, 0x0050($sp)
/* 002D8 80994F28 C6500064 */  lwc1    $f16, 0x0064($s2)          ## 00000064
/* 002DC 80994F2C 46004287 */  neg.s   $f10, $f8
/* 002E0 80994F30 3C014080 */  lui     $at, 0x4080                ## $at = 40800000
/* 002E4 80994F34 46125102 */  mul.s   $f4, $f10, $f18
/* 002E8 80994F38 44816000 */  mtc1    $at, $f12                  ## $f12 = 4.00
/* 002EC 80994F3C 46100182 */  mul.s   $f6, $f0, $f16
/* 002F0 80994F40 46043200 */  add.s   $f8, $f6, $f4
/* 002F4 80994F44 0C00CFBE */  jal     Math_Rand_ZeroFloat

/* 002F8 80994F48 E6480064 */  swc1    $f8, 0x0064($s2)           ## 00000064
/* 002FC 80994F4C 3C014080 */  lui     $at, 0x4080                ## $at = 40800000
/* 00300 80994F50 44815000 */  mtc1    $at, $f10                  ## $f10 = 4.00
/* 00304 80994F54 3C014580 */  lui     $at, 0x4580                ## $at = 45800000
/* 00308 80994F58 44816000 */  mtc1    $at, $f12                  ## $f12 = 4096.00
/* 0030C 80994F5C 460A0480 */  add.s   $f18, $f0, $f10
/* 00310 80994F60 0C00CFC8 */  jal     Math_Rand_CenteredFloat

/* 00314 80994F64 E6520060 */  swc1    $f18, 0x0060($s2)          ## 00000060
/* 00318 80994F68 4600040D */  trunc.w.s $f16, $f0
/* 0031C 80994F6C 3C014580 */  lui     $at, 0x4580                ## $at = 45800000
/* 00320 80994F70 44816000 */  mtc1    $at, $f12                  ## $f12 = 4096.00
/* 00324 80994F74 440B8000 */  mfc1    $t3, $f16
/* 00328 80994F78 0C00CFC8 */  jal     Math_Rand_CenteredFloat

/* 0032C 80994F7C A64B0030 */  sh      $t3, 0x0030($s2)           ## 00000030
/* 00330 80994F80 4600018D */  trunc.w.s $f6, $f0
/* 00334 80994F84 3C014580 */  lui     $at, 0x4580                ## $at = 45800000
/* 00338 80994F88 44816000 */  mtc1    $at, $f12                  ## $f12 = 4096.00
/* 0033C 80994F8C 440D3000 */  mfc1    $t5, $f6
/* 00340 80994F90 0C00CFC8 */  jal     Math_Rand_CenteredFloat

/* 00344 80994F94 A64D0032 */  sh      $t5, 0x0032($s2)           ## 00000032
/* 00348 80994F98 4600010D */  trunc.w.s $f4, $f0
/* 0034C 80994F9C 24180050 */  addiu   $t8, $zero, 0x0050         ## $t8 = 00000050
/* 00350 80994FA0 A658021A */  sh      $t8, 0x021A($s2)           ## 0000021A
/* 00354 80994FA4 440F2000 */  mfc1    $t7, $f4
/* 00358 80994FA8 00000000 */  nop
/* 0035C 80994FAC A64F0034 */  sh      $t7, 0x0034($s2)           ## 00000034
.L80994FB0:
/* 00360 80994FB0 8FBF003C */  lw      $ra, 0x003C($sp)
.L80994FB4:
/* 00364 80994FB4 8FB00024 */  lw      $s0, 0x0024($sp)
/* 00368 80994FB8 8FB10028 */  lw      $s1, 0x0028($sp)
/* 0036C 80994FBC 8FB2002C */  lw      $s2, 0x002C($sp)
/* 00370 80994FC0 8FB30030 */  lw      $s3, 0x0030($sp)
/* 00374 80994FC4 8FB40034 */  lw      $s4, 0x0034($sp)
/* 00378 80994FC8 8FB50038 */  lw      $s5, 0x0038($sp)
/* 0037C 80994FCC 03E00008 */  jr      $ra
/* 00380 80994FD0 27BD0058 */  addiu   $sp, $sp, 0x0058           ## $sp = 00000000
