.late_rodata
glabel D_80875694
    .float 0.4

 .text
glabel func_80872C58
/* 00428 80872C58 27BDFFE0 */  addiu   $sp, $sp, 0xFFE0           ## $sp = FFFFFFE0
/* 0042C 80872C5C AFBF001C */  sw      $ra, 0x001C($sp)           
/* 00430 80872C60 AFB00018 */  sw      $s0, 0x0018($sp)           
/* 00434 80872C64 AFA50024 */  sw      $a1, 0x0024($sp)           
/* 00438 80872C68 C4860320 */  lwc1    $f6, 0x0320($a0)           ## 00000320
/* 0043C 80872C6C C484030C */  lwc1    $f4, 0x030C($a0)           ## 0000030C
/* 00440 80872C70 00808025 */  or      $s0, $a0, $zero            ## $s0 = 00000000
/* 00444 80872C74 3C063DCC */  lui     $a2, 0x3DCC                ## $a2 = 3DCC0000
/* 00448 80872C78 46062000 */  add.s   $f0, $f4, $f6              
/* 0044C 80872C7C 34C6CCCD */  ori     $a2, $a2, 0xCCCD           ## $a2 = 3DCCCCCD
/* 00450 80872C80 24840028 */  addiu   $a0, $a0, 0x0028           ## $a0 = 00000028
/* 00454 80872C84 3C074120 */  lui     $a3, 0x4120                ## $a3 = 41200000
/* 00458 80872C88 44050000 */  mfc1    $a1, $f0                   
/* 0045C 80872C8C 0C01E107 */  jal     Math_SmoothScaleMaxF
              
/* 00460 80872C90 E48002F4 */  swc1    $f0, 0x02F4($a0)           ## 0000031C
/* 00464 80872C94 3C063DCC */  lui     $a2, 0x3DCC                ## $a2 = 3DCC0000
/* 00468 80872C98 34C6CCCD */  ori     $a2, $a2, 0xCCCD           ## $a2 = 3DCCCCCD
/* 0046C 80872C9C 26040320 */  addiu   $a0, $s0, 0x0320           ## $a0 = 00000320
/* 00470 80872CA0 3C054120 */  lui     $a1, 0x4120                ## $a1 = 41200000
/* 00474 80872CA4 0C01E107 */  jal     Math_SmoothScaleMaxF
              
/* 00478 80872CA8 3C073F00 */  lui     $a3, 0x3F00                ## $a3 = 3F000000
/* 0047C 80872CAC 8FAE0024 */  lw      $t6, 0x0024($sp)           
/* 00480 80872CB0 91CF1D6C */  lbu     $t7, 0x1D6C($t6)           ## 00001D6C
/* 00484 80872CB4 55E0000B */  bnel    $t7, $zero, .L80872CE4     
/* 00488 80872CB8 C6100324 */  lwc1    $f16, 0x0324($s0)          ## 00000324
/* 0048C 80872CBC C6080324 */  lwc1    $f8, 0x0324($s0)           ## 00000324
/* 00490 80872CC0 4600428D */  trunc.w.s $f10, $f8                  
/* 00494 80872CC4 44045000 */  mfc1    $a0, $f10                  
/* 00498 80872CC8 00000000 */  nop
/* 0049C 80872CCC 00042400 */  sll     $a0, $a0, 16               
/* 004A0 80872CD0 0C01DE1C */  jal     Math_Sins
              ## sins?
/* 004A4 80872CD4 00042403 */  sra     $a0, $a0, 16               
/* 004A8 80872CD8 1000000C */  beq     $zero, $zero, .L80872D0C   
/* 004AC 80872CDC E6000060 */  swc1    $f0, 0x0060($s0)           ## 00000060
/* 004B0 80872CE0 C6100324 */  lwc1    $f16, 0x0324($s0)          ## 00000324
.L80872CE4:
/* 004B4 80872CE4 4600848D */  trunc.w.s $f18, $f16                 
/* 004B8 80872CE8 44049000 */  mfc1    $a0, $f18                  
/* 004BC 80872CEC 00000000 */  nop
/* 004C0 80872CF0 00042400 */  sll     $a0, $a0, 16               
/* 004C4 80872CF4 0C01DE1C */  jal     Math_Sins
              ## sins?
/* 004C8 80872CF8 00042403 */  sra     $a0, $a0, 16               
/* 004CC 80872CFC 3C018087 */  lui     $at, %hi(D_80875694)       ## $at = 80870000
/* 004D0 80872D00 C4245694 */  lwc1    $f4, %lo(D_80875694)($at)  
/* 004D4 80872D04 46040182 */  mul.s   $f6, $f0, $f4              
/* 004D8 80872D08 E6060060 */  swc1    $f6, 0x0060($s0)           ## 00000060
.L80872D0C:
/* 004DC 80872D0C 8FBF001C */  lw      $ra, 0x001C($sp)           
/* 004E0 80872D10 8FB00018 */  lw      $s0, 0x0018($sp)           
/* 004E4 80872D14 27BD0020 */  addiu   $sp, $sp, 0x0020           ## $sp = 00000000
/* 004E8 80872D18 03E00008 */  jr      $ra                        
/* 004EC 80872D1C 00000000 */  nop
