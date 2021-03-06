#ifndef _Z64ACTOR_H_
#define _Z64ACTOR_H_

#include <z64animation.h>
#include <z64math.h>
#include <z64collision_check.h>

#define ACTOR_NUMBER_MAX 200
#define INVISIBLE_ACTOR_MAX 20
#define AM_FIELD_SIZE 0x27A0

// From z64.h
struct Actor;
struct GlobalContext;

// From z64light.h
struct Lights;

typedef struct {
    Vec3f pos;
    Vec3s rot;
} PosRot; // size = 0x14

typedef struct {
    /* 0x00 */ char   unk_00[0x8];
    /* 0x08 */ Vec3s  norm;  // Normal vector
    /* 0x0E */ s16    dist;  // Plane distance from origin
} CollisionPoly; // size = 0x10

typedef void (*ActorFunc)(struct Actor*, struct GlobalContext*);
typedef u16 (*callback1_800343CC)(struct GlobalContext*, struct Actor*);
typedef s16 (*callback2_800343CC)(struct GlobalContext*, struct Actor*);

typedef struct {
    /* 0x00 */ s16 id;
    /* 0x02 */ u8  type; // Classifies actor and determines when actor will execute
    /* 0x04 */ u32 flags;
    /* 0x08 */ s16 objectId;
    /* 0x0C */ u32 instanceSize;
    /* 0x10 */ ActorFunc init; // Constructor
    /* 0x14 */ ActorFunc destroy; // Destructor
    /* 0x18 */ ActorFunc update; // Main Update Function
    /* 0x1C */ ActorFunc draw; // Draw function
} ActorInit; // size = 0x20

typedef enum {
    ALLOCTYPE_NORMAL,
    ALLOCTYPE_ABSOLUTE,
    ALLOCTYPE_PERMANENT
} AllocType;

typedef struct {
    /* 0x00 */ u32   vromStart;
    /* 0x04 */ u32   vromEnd;
    /* 0x08 */ void* vramStart;
    /* 0x0C */ void* vramEnd;
    /* 0x10 */ void* loadedRamAddr; // original name: "allocp"
    /* 0x14 */ ActorInit* initInfo;
    /* 0x18 */ char* name;
    /* 0x1C */ u16   allocType;
    /* 0x1E */ s8    nbLoaded; // original name: "clients"
} ActorOverlay; // size = 0x20

typedef struct {
    u8 table[32];
} DamageTable;

typedef struct {
    /* 0x00 */ u8 health;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ u8 mass;
} CollisionCheckInfoInit;

typedef struct {
    /* 0x00 */ u8 health;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ u8 mass;
} CollisionCheckInfoInit2;

typedef struct {
    /* 0x00 */ DamageTable* damageTable;  // For actors which contain one (example: Stalfos)...
    /* 0x04 */ Vec3f displacement; // Amount to correct velocity (0x5C) by when colliding into a body
    /* 0x10 */ s16   unk_10;
    /* 0x12 */ s16   unk_12;
    /* 0x14 */ u16   unk_14;
    /* 0x16 */ u8    mass; // Used to compute displacement, 50 is common value, 0xFF for infinite mass/unmoveable
    /* 0x17 */ u8    health;
    /* 0x18 */ u8    damage; // Amount to decrement health by
    /* 0x19 */ u8    damageEffect; // Stores what effect should occur when hit by a weapon
    /* 0x1A */ u8    atHitEffect; // Stores what effect should occur when AT connects with an AC
    /* 0x1B */ u8    acHitEffect; // Stores what effect should occur when AC is touched by an AT
} CollisionCheckInfo; // size = 0x1C

typedef struct {
    /* 0x00 */ Vec3s  rot; // Current actor shape rotation
    /* 0x06 */ u8     unk_06;
    /* 0x08 */ f32    unk_08; // Model y axis offset. Represents model space units. collision mesh related
    /* 0x0C */ void (*shadowDrawFunc)(struct Actor*, struct Lights*, struct GlobalContext*);
    /* 0x10 */ f32    unk_10;
    /* 0x14 */ u8     unk_14;
    /* 0x15 */ u8     unk_15;
} ActorShape; // size = 0x18

typedef struct Actor {
    /* 0x000 */ s16     id; // Actor Id
    /* 0x002 */ u8      type; // Actor Type. Refer to the corresponding enum for values
    /* 0x003 */ s8      room; // Room number the actor is in. -1 denotes that the actor won't despawn on a room change
    /* 0x004 */ u32     flags; // Flags used for various purposes
    /* 0x008 */ PosRot  initPosRot; // Initial position/rotation when spawned. Is sometimes used for other purposes
    /* 0x01C */ s16     params; // original name: "args_data"; Configurable variable set by an actor's spawn data
    /* 0x01E */ s8      objBankIndex; // original name: "bank"; Object bank index of this actor's object dependency
    /* 0x01F */ s8      unk_1F;
    /* 0x020 */ u16     sfx; // Plays sound effect relative to actor's location (if within range of camera?)
    /* 0x024 */ PosRot  posRot; // position/rotation in the world
    /* 0x038 */ PosRot  posRot2;
    /* 0x04C */ f32     unk_4C;
    /* 0x050 */ Vec3f   scale; // Sets x,y,z scaling factor. Typically, a factor of 0.01 is used for each axis
    /* 0x05C */ Vec3f   velocity;
    /* 0x068 */ f32     speedXZ; // Always positive, stores how fast the actor is traveling along the XZ plane
    /* 0x06C */ f32     gravity; // Acceleration due to gravity; value is added to Y velocity every frame
    /* 0x070 */ f32     minVelocityY; // Sets the lower bounds cap on velocity along the Y axis
    /* 0x074 */ CollisionPoly* wallPoly; // Wall polygon an actor is touching
    /* 0x078 */ CollisionPoly* floorPoly; // Floor polygon an actor is over/touching
    /* 0x07C */ u8      wallPolySource; // Complex Poly Surface Source. 0x32 = Scene
    /* 0x07D */ u8      floorPolySource; // Complex Poly Surface Source. 0x32 = Scene. related to 0x80/88
    /* 0x07E */ s16     wallPolyRot; // Rotation of the wall poly an actor is touching
    /* 0x080 */ f32     groundY;
    /* 0x084 */ f32     waterY;
    /* 0x088 */ u16     bgCheckFlags;
    /* 0x08A */ s16     yawTowardsLink;
    /* 0x08C */ f32     xyzDistFromLinkSq;
    /* 0x090 */ f32     xzDistFromLink;
    /* 0x094 */ f32     yDistFromLink;
    /* 0x098 */ CollisionCheckInfo colChkInfo;
    /* 0x0B4 */ ActorShape shape;
    /* 0x0CC */ Vec3f   unk_CC[2];
    /* 0x0E4 */ Vec3f   projectedPos; // actor position in projected space
    /* 0x0F0 */ f32     projectedW; // w component of the projected actor position vector
    /* 0x0F4 */ f32     uncullZoneForward; // amount to increase the uncull zone forward by (in projected space)
    /* 0x0F8 */ f32     uncullZoneScale; // amount to increase the uncull zone scale by (in projected space)
    /* 0x0FC */ f32     uncullZoneDownward; // amount to increase uncull zone downward by (in projected space)
    /* 0x100 */ Vec3f   pos4;
    /* 0x10C */ u8      unk_10C; // Z-Target related
    /* 0x10D */ u8      unk_10D; // Z-Target related
    /* 0x10E */ u16     textId; // Text id to pass to link/display when interacting with an actor
    /* 0x110 */ u16     freezeTimer;
    /* 0x112 */ u16     dmgEffectParams; // Specifies damage effect color (white/red/blue) and if opaque or translucent
    /* 0x114 */ u8      dmgEffectTimer;
    /* 0x115 */ u8      isDrawn; // Indicates whether the actor is currently being drawn (but not seen through lens)
    /* 0x116 */ u8      unk_116;
    /* 0x117 */ u8      naviEnemyId; // Sets what 0600 dialog to display when talking to navi. Default 0xFF
    /* 0x118 */ struct Actor* parent;
    /* 0x11C */ struct Actor* child;
    /* 0x120 */ struct Actor* prev; // Previous Actor of this type
    /* 0x124 */ struct Actor* next; // Next Actor of this type
    /* 0x128 */ ActorFunc init; // Initialization Routine. Called by Actor_Init or Actor_UpdateAll
    /* 0x12C */ ActorFunc destroy; // Destruction Routine. Called by Actor_Destroy
    /* 0x130 */ ActorFunc update; // Update Routine. Called by Actor_UpdateAll
    /* 0x134 */ ActorFunc draw; // Draw Routine. Called by Actor_Draw
    /* 0x138 */ ActorOverlay* overlayEntry; // Pointer to the overlay table entry for this actor
    /* 0x13C */ char    dbgPad[0x10]; // Padding that only exists in the debug rom
} Actor; // size = 0x14C

typedef struct {
    /* 0x00 */ char unk_00[0x04];
    /* 0x04 */ Actor* actor;
    /* 0x08 */ void* unk_08; // Struct800417A0*
    /* 0x0C */ char  unk_0C[0x0C];
    /* 0x18 */ Vec3f scale1;
    /* 0x24 */ Vec3s rot1;
    /* 0x2C */ Vec3f pos1;
    /* 0x38 */ Vec3f scale2;
    /* 0x44 */ Vec3s rot2;
    /* 0x4C */ Vec3f pos2;
    /* 0x58 */ char  unk_58[0x0C];
} ActorMesh; // size = 0x64

typedef struct {
    /* 0x000 */ Actor actor;
    /* 0x14C */ u32 dynaPolyId;
    /* 0x150 */ f32 unk_150;
    /* 0x154 */ f32 unk_154;
    /* 0x158 */ s16 unk_158;
    /* 0x15A */ u16 unk_15A;
    /* 0x15C */ u32 unk_15C;
    /* 0x160 */ u8 unk_160;
    /* 0x162 */ s16 unk_162;
} DynaPolyActor; // size = 0x164

typedef struct {
    /* 0x00 */ s32 active;
    /* 0x04 */ Vec3f tip;
    /* 0x10 */ Vec3f base;
} Struct_80090480_arg2;

typedef struct {
    /* 0x00 */ MtxF* unk_00;
    /* 0x04 */ s16* unk_04;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ char unk_0A[0x02];
    /* 0x0C */ s32* unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
} struct_80032E24;

struct Player;

typedef void (*PlayerActionFunc)(struct Player*, struct GlobalContext*);

typedef struct Player {
    /* 0x0000 */ Actor      actor;
    /* 0x014C */ s8         currentTunic;
    /* 0x014D */ s8         currentSword;
    /* 0x014E */ s8         currentShield;
    /* 0x014F */ s8         currentBoots;
    /* 0x0150 */ s8         heldItemCButtonIdx;
    /* 0x0151 */ s8         heldItemActionParam;
    /* 0x0152 */ s8         unk_152;
    /* 0x0153 */ s8         unk_153;
    /* 0x0154 */ s8         unk_154;
    /* 0x0155 */ char       unk_155[0x003];
    /* 0x0158 */ s8         unk_158;
    /* 0x0159 */ char       unk_159[0x002];
    /* 0x015B */ u8         unk_15B;
    /* 0x015C */ u8         unk_15C;
    /* 0x015D */ u8         unk_15D;
    /* 0x015E */ u8         unk_15E;
    /* 0x015F */ u8         currentMask;
    /* 0x0160 */ UNK_PTR    unk_160;
    /* 0x0164 */ UNK_PTR    unk_164;
    /* 0x0168 */ UNK_PTR    unk_168;
    /* 0x016C */ UNK_PTR    unk_16C;
    /* 0x0170 */ u8         unk_170;
    /* 0x0171 */ char       unk_171[0x023];
    /* 0x0194 */ OSMesgQueue unk_194;
    /* 0x01AC */ char       unk_1AC[0x004];
    /* 0x01B0 */ void*      getItemModel; // Pointer to the space where the get item model is allocated
    /* 0x01B4 */ SkelAnime  skelAnime;
    /* 0x01F8 */ char        unk_1F8[0x1B4];
    /* 0x03AC */ Actor*     heldActor;
    /* 0x03B0 */ Vec3f      unk_3B0; // related to links hands
    /* 0x03BC */ char       unk_3BC[0x00C];
    /* 0x03C8 */ Vec3f      unk_3C8;
    /* 0x03D4 */ char       unk_3D4[0x058];
    /* 0x042C */ s8         unk_42C;
    /* 0x042D */ s8         unk_42D;
    /* 0x042E */ s16        unk_42E;
    /* 0x0430 */ Actor*     unk_430;
    /* 0x0434 */ u8         getItemId;
    /* 0x0435 */ char       unk_435[0x001];
    /* 0x0436 */ u16        getItemDirection;
    /* 0x0438 */ Actor*     interactRangeActor;
    /* 0x043C */ s8         unk_43C;
    /* 0x043D */ char       unk_43D[0x003];
    /* 0x0440 */ Actor*     rideActor;
    /* 0x0444 */ u8         action;
    /* 0x0445 */ char       unk_445[0x003];
    /* 0x0448 */ Actor*     unk_448;
    /* 0x044C */ char       unk_44C[0x004];
    /* 0x0450 */ Vec3f      unk_450;
    /* 0x045C */ char       unk_45C[0x00E];
    /* 0x046A */ u16        unk_46A;
    /* 0x046C */ char       unk_46C[0x06E];
    /* 0x04DA */ s16        unk_4DA;
    /* 0x04DC */ char       unk_4DC[0x008];
    /* 0x04E4 */ Collider   unk_4E4; // TODO determine type
    /* 0x04FC */ char       unk_4FC[0x068];
    /* 0x0564 */ Collider   unk_564; // TODO determine type
    /* 0x057C */ char       unk_57C[0x07C];
    /* 0x05F8 */ u8         unk_5F8;
    /* 0x05F9 */ char       unk_5F9[0x06B];
    /* 0x0664 */ Actor*     unk_664;
    /* 0x0668 */ char       unk_668[0x004];
    /* 0x066C */ s32        unk_66C;
    /* 0x0670 */ u32        swordEffectId;
    /* 0x0674 */ PlayerActionFunc  actionFunc;
    /* 0x0678 */ u32        ageProperties;
    /* 0x067C */ u32        stateFlags1;
    /* 0x0680 */ u32        stateFlags2;
    /* 0x0684 */ Actor*     unk_684;
    /* 0x0688 */ char       unk_688[0x004];
    /* 0x068C */ Actor*     navi;
    /* 0x0690 */ s16        naviMessageId;
    /* 0x0692 */ u8         unk_692;
    /* 0x0693 */ s8         exchangeItemId;
    /* 0x0694 */ Actor*     naviTargetActor;
    /* 0x0698 */ f32        targetActorDistance;
    /* 0x069C */ char       unk_69C[0x008];
    /* 0x06A4 */ f32        unk_6A4;
    /* 0x06A8 */ Actor*     unk_6A8;
    /* 0x06AC */ char       unk_6AC[0x001];
    /* 0x06AD */ u8         unk_6AD;
    /* 0x06AE */ char       unk_6AE[0x2];
    /* 0x06B0 */ s16        unk_6B0;
    /* 0x06B2 */ char       unk_6B4[0x4];
    /* 0x06B6 */ Vec3s      unk_6B6;
    /* 0x06BC */ s16        unk_6BC;
    /* 0x06BE */ s16        unk_6BE;
    /* 0x06C0 */ s16        unk_6C0;
    /* 0x06C2 */ s16        unk_6C2;
    /* 0x06C4 */ f32        unk_6C4;
    /* 0x06C8 */ SkelAnime  skelAnime2;
    /* 0x070C */ char       unk_70C[0x128];
    /* 0x0834 */ s16        unk_834;
    /* 0x0836 */ char       unk_836[0x002];
    /* 0x0838 */ f32        linearVelocity;
    /* 0x083C */ s16        currentYaw;
    /* 0x083E */ s16        targetYaw;
    /* 0x0840 */ u16        unk_840;
    /* 0x0842 */ s8         swordAnimation;
    /* 0x0843 */ s8         swordState;
    /* 0x0844 */ u8         unk_844;
    /* 0x0845 */ u8         unk_845;
    /* 0x0846 */ u8         unk_846;
    /* 0x0847 */ char       unk_847[0x004];
    /* 0x084B */ s8         unk_84B[4];
    /* 0x084F */ s8         unk_84F;
    /* 0x0850 */ s16        unk_850;
    /* 0x0852 */ char       unk_852[0x00A];
    /* 0x085C */ f32        stickLength;
    /* 0x0860 */ s16        stickFlameTimer;
    /* 0x0862 */ s8         overheadItemId;
    /* 0x0863 */ char       unk_863[0x021];

    /* 0x0884 */ f32        ledgeDistance; // The distance from link to a grabbable ledge
    // Only updates if pushing against a wall with a grabbable ledge above
    // If the ledge is too high to grab the value is 399.96f

    /* 0x0888 */ f32        wallDistance; // Only updates if pushing against a wall with a grabbable ledge above
    /* 0x088C */ char       unk_88C[0x008];
    /* 0x0894 */ s16        dropY; // Truncated copy of y position that does not update while falling
    /* 0x0896 */ s16        fallY; // The truncated y distance link has moved in that frame, positive is down, negative is up
    /* 0x0898 */ char       unk_898[0x008];
    /* 0x08A0 */ u8         unk_8A0;
    /* 0x08A1 */ u8         unk_8A1;
    /* 0x08A2 */ u16        unk_8A2;
    /* 0x08A4 */ f32        unk_8A4;
    /* 0x08A8 */ f32        unk_8A8;
    /* 0x08AC */ f32        fanWindSpeed;
    /* 0x08B0 */ s16        fanWindDirection;
    /* 0x08B2 */ char       unk_8B2[0x002];
    /* 0x08B4 */ Struct_80090480_arg2 swordDimensions; // Trail active, tip, base?
    /* 0x08D0 */ Struct_80090480_arg2 unk_8D0;
    /* 0x08EC */ Struct_80090480_arg2 unk_8EC;
    /* 0x0908 */ char       unk_908[0x04];
    /* 0x090C */ f32        unk_90C;
    /* 0x0910 */ char       unk_910[0x4C];
    /* 0x095C */ Vec3f      unk_95C;
    /* 0x0968 */ char       unk_968[0x78];
    /* 0x09E0 */ MtxF       mf_9E0;
    /* 0x0A20 */ MtxF       mf_A20;
    /* 0x0A60 */ char       unk_A60[0x08];
    /* 0x0A68 */ s8         unk_A68;
    /* 0x0A69 */ char       unk_A6A[0x0F];

    /* 0x0A78 */ s8         invincibilityTimer; // Take no damage if this value is nonzero
    // Positive induces red flashing, negative does not
    // Counts towards zero each frame

    /* 0x0A79 */ char       unk_A79[0x1B];
} Player; // size = 0xA94

typedef enum {
    /* 0x00 */ ITEM00_RUPEE_GREEN,
    /* 0x01 */ ITEM00_RUPEE_BLUE,
    /* 0x02 */ ITEM00_RUPEE_RED,
    /* 0x03 */ ITEM00_HEART,
    /* 0x04 */ ITEM00_BOMBS_A,
    /* 0x05 */ ITEM00_ARROWS_SINGLE,
    /* 0x06 */ ITEM00_HEART_PIECE,
    /* 0x07 */ ITEM00_HEART_CONTAINER,
    /* 0x08 */ ITEM00_ARROWS_SMALL,
    /* 0x09 */ ITEM00_ARROWS_MEDIUM,
    /* 0x0A */ ITEM00_ARROWS_LARGE,
    /* 0x0B */ ITEM00_BOMBS_B,
    /* 0x0C */ ITEM00_NUTS,
    /* 0x0D */ ITEM00_STICK,
    /* 0x0E */ ITEM00_MAGIC_LARGE,
    /* 0x0F */ ITEM00_MAGIC_SMALL,
    /* 0x10 */ ITEM00_SEEDS,
    /* 0x11 */ ITEM00_SMALL_KEY,
    /* 0x12 */ ITEM00_FLEXIBLE,
    /* 0x13 */ ITEM00_RUPEE_ORANGE,
    /* 0x14 */ ITEM00_RUPEE_PURPLE,
    /* 0x15 */ ITEM00_SHIELD_DEKU,
    /* 0x16 */ ITEM00_SHIELD_HYLIAN,
    /* 0x17 */ ITEM00_TUNIC_ZORA,
    /* 0x18 */ ITEM00_TUNIC_GORON,
    /* 0x19 */ ITEM00_BOMBS_SPECIAL
} Item00Type;

struct EnItem00;

typedef void (*EnItem00ActionFunc)(struct EnItem00*, struct GlobalContext*);

typedef struct EnItem00 {
    /* 0x000 */ Actor actor;
    /* 0x14C */ EnItem00ActionFunc actionFunc;
    /* 0x150 */ s16 collectibleFlag;
    /* 0x152 */ s16 unk_152;
    /* 0x154 */ s16 unk_154;
    /* 0x156 */ s16 unk_156;
    /* 0x158 */ s16 unk_158;
    /* 0x15A */ s16 unk_15A;
    /* 0x15C */ f32 unk_15C;
    /* 0x160 */ ColliderCylinder collider;
} EnItem00; // size = 0x1AC

typedef enum {
    /* 0x00 */ A_OBJ_BLOCK_SMALL,
    /* 0x01 */ A_OBJ_BLOCK_LARGE,
    /* 0x02 */ A_OBJ_BLOCK_HUGE,
    /* 0x03 */ A_OBJ_BLOCK_SMALL_ROT,
    /* 0x04 */ A_OBJ_BLOCK_LARGE_ROT,
    /* 0x05 */ A_OBJ_CUBE_SMALL,
    /* 0x06 */ A_OBJ_UNKNOWN_6,
    /* 0x07 */ A_OBJ_GRASS_CLUMP,
    /* 0x08 */ A_OBJ_TREE_STUMP,
    /* 0x09 */ A_OBJ_SIGNPOST_OBLONG,
    /* 0x0A */ A_OBJ_SIGNPOST_ARROW,
    /* 0x0B */ A_OBJ_KNOB
} AObjType;

struct EnAObj;

typedef void (*EnAObjActionFunc)(struct EnAObj*, struct GlobalContext*);

typedef struct EnAObj {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x164 */ EnAObjActionFunc actionFunc;
    /* 0x168 */ s32 unk_168;
    /* 0x16C */ s16 textId;
    /* 0x16E */ s16 unk_16E;
    /* 0x170 */ s16 unk_170;
    /* 0x172 */ s16 unk_172;
    /* 0x174 */ s16 unk_174;
    /* 0x178 */ f32 unk_178;
    /* 0x17C */ ColliderCylinder collider;
} EnAObj; // size = 0x1C8

typedef enum {
    /* 0x00 */ ACTORTYPE_SWITCH,
    /* 0x01 */ ACTORTYPE_BG,
    /* 0x02 */ ACTORTYPE_PLAYER,
    /* 0x03 */ ACTORTYPE_EXPLOSIVES,
    /* 0x04 */ ACTORTYPE_NPC,
    /* 0x05 */ ACTORTYPE_ENEMY,
    /* 0x06 */ ACTORTYPE_PROP,
    /* 0x07 */ ACTORTYPE_ITEMACTION,
    /* 0x08 */ ACTORTYPE_MISC,
    /* 0x09 */ ACTORTYPE_BOSS,
    /* 0x0A */ ACTORTYPE_DOOR,
    /* 0x0B */ ACTORTYPE_CHEST
} ActorType;

typedef enum {
    /* 0x0000 */ ACTOR_PLAYER,
    /* 0x0001 */ ACTOR_UNSET_1,
    /* 0x0002 */ ACTOR_EN_TEST,
    /* 0x0003 */ ACTOR_UNSET_3,
    /* 0x0004 */ ACTOR_EN_GIRLA,
    /* 0x0005 */ ACTOR_UNSET_5,
    /* 0x0006 */ ACTOR_UNSET_6,
    /* 0x0007 */ ACTOR_EN_PART,
    /* 0x0008 */ ACTOR_EN_LIGHT,
    /* 0x0009 */ ACTOR_EN_DOOR,
    /* 0x000A */ ACTOR_EN_BOX, // Treasure Chest
    /* 0x000B */ ACTOR_BG_DY_YOSEIZO,
    /* 0x000C */ ACTOR_BG_HIDAN_FIREWALL,
    /* 0x000D */ ACTOR_EN_POH,
    /* 0x000E */ ACTOR_EN_OKUTA,
    /* 0x000F */ ACTOR_BG_YDAN_SP,
    /* 0x0010 */ ACTOR_EN_BOM,
    /* 0x0011 */ ACTOR_EN_WALLMAS,
    /* 0x0012 */ ACTOR_EN_DODONGO,
    /* 0x0013 */ ACTOR_EN_FIREFLY,
    /* 0x0014 */ ACTOR_EN_HORSE,
    /* 0x0015 */ ACTOR_EN_ITEM00,
    /* 0x0016 */ ACTOR_EN_ARROW,
    /* 0x0017 */ ACTOR_UNSET_17,
    /* 0x0018 */ ACTOR_EN_ELF,
    /* 0x0019 */ ACTOR_EN_NIW,
    /* 0x001A */ ACTOR_UNSET_1A,
    /* 0x001B */ ACTOR_EN_TITE,
    /* 0x001C */ ACTOR_EN_REEBA,
    /* 0x001D */ ACTOR_EN_PEEHAT,
    /* 0x001E */ ACTOR_EN_BUTTE,
    /* 0x001F */ ACTOR_UNSET_1F,
    /* 0x0020 */ ACTOR_EN_INSECT,
    /* 0x0021 */ ACTOR_EN_FISH,
    /* 0x0022 */ ACTOR_UNSET_22,
    /* 0x0023 */ ACTOR_EN_HOLL,
    /* 0x0024 */ ACTOR_EN_SCENE_CHANGE,
    /* 0x0025 */ ACTOR_EN_ZF,
    /* 0x0026 */ ACTOR_EN_HATA,
    /* 0x0027 */ ACTOR_BOSS_DODONGO,
    /* 0x0028 */ ACTOR_BOSS_GOMA,
    /* 0x0029 */ ACTOR_EN_ZL1,
    /* 0x002A */ ACTOR_EN_VIEWER,
    /* 0x002B */ ACTOR_EN_GOMA,
    /* 0x002C */ ACTOR_BG_PUSHBOX,
    /* 0x002D */ ACTOR_EN_BUBBLE,
    /* 0x002E */ ACTOR_DOOR_SHUTTER,
    /* 0x002F */ ACTOR_EN_DODOJR,
    /* 0x0030 */ ACTOR_EN_BDFIRE,
    /* 0x0031 */ ACTOR_UNSET_31,
    /* 0x0032 */ ACTOR_EN_BOOM,
    /* 0x0033 */ ACTOR_EN_TORCH2,
    /* 0x0034 */ ACTOR_EN_BILI,
    /* 0x0035 */ ACTOR_EN_TP,
    /* 0x0036 */ ACTOR_UNSET_36,
    /* 0x0037 */ ACTOR_EN_ST,
    /* 0x0038 */ ACTOR_EN_BW,
    /* 0x0039 */ ACTOR_EN_A_OBJ,
    /* 0x003A */ ACTOR_EN_EIYER,
    /* 0x003B */ ACTOR_EN_RIVER_SOUND,
    /* 0x003C */ ACTOR_EN_HORSE_NORMAL,
    /* 0x003D */ ACTOR_EN_OSSAN,
    /* 0x003E */ ACTOR_BG_TREEMOUTH,
    /* 0x003F */ ACTOR_BG_DODOAGO,
    /* 0x0040 */ ACTOR_BG_HIDAN_DALM,
    /* 0x0041 */ ACTOR_BG_HIDAN_HROCK,
    /* 0x0042 */ ACTOR_EN_HORSE_GANON,
    /* 0x0043 */ ACTOR_BG_HIDAN_ROCK,
    /* 0x0044 */ ACTOR_BG_HIDAN_RSEKIZOU,
    /* 0x0045 */ ACTOR_BG_HIDAN_SEKIZOU,
    /* 0x0046 */ ACTOR_BG_HIDAN_SIMA,
    /* 0x0047 */ ACTOR_BG_HIDAN_SYOKU,
    /* 0x0048 */ ACTOR_EN_XC,
    /* 0x0049 */ ACTOR_BG_HIDAN_CURTAIN,
    /* 0x004A */ ACTOR_BG_SPOT00_HANEBASI,
    /* 0x004B */ ACTOR_EN_MB,
    /* 0x004C */ ACTOR_EN_BOMBF,
    /* 0x004D */ ACTOR_EN_ZL2,
    /* 0x004E */ ACTOR_BG_HIDAN_FSLIFT,
    /* 0x004F */ ACTOR_EN_OE2,
    /* 0x0050 */ ACTOR_BG_YDAN_HASI,
    /* 0x0051 */ ACTOR_BG_YDAN_MARUTA,
    /* 0x0052 */ ACTOR_BOSS_GANONDROF,
    /* 0x0053 */ ACTOR_UNSET_53,
    /* 0x0054 */ ACTOR_EN_AM,
    /* 0x0055 */ ACTOR_EN_DEKUBABA,
    /* 0x0056 */ ACTOR_EN_M_FIRE1,
    /* 0x0057 */ ACTOR_EN_M_THUNDER,
    /* 0x0058 */ ACTOR_BG_DDAN_JD,
    /* 0x0059 */ ACTOR_BG_BREAKWALL,
    /* 0x005A */ ACTOR_EN_JJ,
    /* 0x005B */ ACTOR_EN_HORSE_ZELDA,
    /* 0x005C */ ACTOR_BG_DDAN_KD,
    /* 0x005D */ ACTOR_DOOR_WARP1,
    /* 0x005E */ ACTOR_OBJ_SYOKUDAI,
    /* 0x005F */ ACTOR_ITEM_B_HEART,
    /* 0x0060 */ ACTOR_EN_DEKUNUTS,
    /* 0x0061 */ ACTOR_BG_MENKURI_KAITEN,
    /* 0x0062 */ ACTOR_BG_MENKURI_EYE,
    /* 0x0063 */ ACTOR_EN_VALI,
    /* 0x0064 */ ACTOR_BG_MIZU_MOVEBG,
    /* 0x0065 */ ACTOR_BG_MIZU_WATER,
    /* 0x0066 */ ACTOR_ARMS_HOOK,
    /* 0x0067 */ ACTOR_EN_FHG,
    /* 0x0068 */ ACTOR_BG_MORI_HINERI,
    /* 0x0069 */ ACTOR_EN_BB,
    /* 0x006A */ ACTOR_BG_TOKI_HIKARI,
    /* 0x006B */ ACTOR_EN_YUKABYUN,
    /* 0x006C */ ACTOR_BG_TOKI_SWD,
    /* 0x006D */ ACTOR_EN_FHG_FIRE,
    /* 0x006E */ ACTOR_BG_MJIN,
    /* 0x006F */ ACTOR_BG_HIDAN_KOUSI,
    /* 0x0070 */ ACTOR_DOOR_TOKI,
    /* 0x0071 */ ACTOR_BG_HIDAN_HAMSTEP,
    /* 0x0072 */ ACTOR_EN_BIRD,
    /* 0x0073 */ ACTOR_UNSET_73,
    /* 0x0074 */ ACTOR_UNSET_74,
    /* 0x0075 */ ACTOR_UNSET_75,
    /* 0x0076 */ ACTOR_UNSET_76,
    /* 0x0077 */ ACTOR_EN_WOOD02,
    /* 0x0078 */ ACTOR_UNSET_78,
    /* 0x0079 */ ACTOR_UNSET_79,
    /* 0x007A */ ACTOR_UNSET_7A,
    /* 0x007B */ ACTOR_UNSET_7B,
    /* 0x007C */ ACTOR_EN_LIGHTBOX,
    /* 0x007D */ ACTOR_EN_PU_BOX,
    /* 0x007E */ ACTOR_UNSET_7E,
    /* 0x007F */ ACTOR_UNSET_7F,
    /* 0x0080 */ ACTOR_EN_TRAP,
    /* 0x0081 */ ACTOR_EN_AROW_TRAP,
    /* 0x0082 */ ACTOR_EN_VASE,
    /* 0x0083 */ ACTOR_UNSET_83,
    /* 0x0084 */ ACTOR_EN_TA,
    /* 0x0085 */ ACTOR_EN_TK,
    /* 0x0086 */ ACTOR_BG_MORI_BIGST,
    /* 0x0087 */ ACTOR_BG_MORI_ELEVATOR,
    /* 0x0088 */ ACTOR_BG_MORI_KAITENKABE,
    /* 0x0089 */ ACTOR_BG_MORI_RAKKATENJO,
    /* 0x008A */ ACTOR_EN_VM,
    /* 0x008B */ ACTOR_DEMO_EFFECT,
    /* 0x008C */ ACTOR_DEMO_KANKYO,
    /* 0x008D */ ACTOR_BG_HIDAN_FWBIG,
    /* 0x008E */ ACTOR_EN_FLOORMAS,
    /* 0x008F */ ACTOR_EN_HEISHI1,
    /* 0x0090 */ ACTOR_EN_RD,
    /* 0x0091 */ ACTOR_EN_PO_SISTERS,
    /* 0x0092 */ ACTOR_BG_HEAVY_BLOCK,
    /* 0x0093 */ ACTOR_BG_PO_EVENT,
    /* 0x0094 */ ACTOR_OBJ_MURE,
    /* 0x0095 */ ACTOR_EN_SW,
    /* 0x0096 */ ACTOR_BOSS_FD,
    /* 0x0097 */ ACTOR_OBJECT_KANKYO,
    /* 0x0098 */ ACTOR_EN_DU,
    /* 0x0099 */ ACTOR_EN_FD,
    /* 0x009A */ ACTOR_EN_HORSE_LINK_CHILD,
    /* 0x009B */ ACTOR_DOOR_ANA,
    /* 0x009C */ ACTOR_BG_SPOT02_OBJECTS,
    /* 0x009D */ ACTOR_BG_HAKA,
    /* 0x009E */ ACTOR_MAGIC_WIND,
    /* 0x009F */ ACTOR_MAGIC_FIRE,
    /* 0x00A0 */ ACTOR_UNSET_A0,
    /* 0x00A1 */ ACTOR_EN_RU1,
    /* 0x00A2 */ ACTOR_BOSS_FD2,
    /* 0x00A3 */ ACTOR_EN_FD_FIRE,
    /* 0x00A4 */ ACTOR_EN_DH,
    /* 0x00A5 */ ACTOR_EN_DHA,
    /* 0x00A6 */ ACTOR_EN_RL,
    /* 0x00A7 */ ACTOR_EN_ENCOUNT1,
    /* 0x00A8 */ ACTOR_DEMO_DU,
    /* 0x00A9 */ ACTOR_DEMO_IM,
    /* 0x00AA */ ACTOR_DEMO_TRE_LGT,
    /* 0x00AB */ ACTOR_EN_FW,
    /* 0x00AC */ ACTOR_BG_VB_SIMA,
    /* 0x00AD */ ACTOR_EN_VB_BALL,
    /* 0x00AE */ ACTOR_BG_HAKA_MEGANE,
    /* 0x00AF */ ACTOR_BG_HAKA_MEGANEBG,
    /* 0x00B0 */ ACTOR_BG_HAKA_SHIP,
    /* 0x00B1 */ ACTOR_BG_HAKA_SGAMI,
    /* 0x00B2 */ ACTOR_UNSET_B2,
    /* 0x00B3 */ ACTOR_EN_HEISHI2,
    /* 0x00B4 */ ACTOR_EN_ENCOUNT2,
    /* 0x00B5 */ ACTOR_EN_FIRE_ROCK,
    /* 0x00B6 */ ACTOR_EN_BROB,
    /* 0x00B7 */ ACTOR_MIR_RAY,
    /* 0x00B8 */ ACTOR_BG_SPOT09_OBJ,
    /* 0x00B9 */ ACTOR_BG_SPOT18_OBJ,
    /* 0x00BA */ ACTOR_BOSS_VA,
    /* 0x00BB */ ACTOR_BG_HAKA_TUBO,
    /* 0x00BC */ ACTOR_BG_HAKA_TRAP,
    /* 0x00BD */ ACTOR_BG_HAKA_HUTA,
    /* 0x00BE */ ACTOR_BG_HAKA_ZOU,
    /* 0x00BF */ ACTOR_BG_SPOT17_FUNEN,
    /* 0x00C0 */ ACTOR_EN_SYATEKI_ITM,
    /* 0x00C1 */ ACTOR_EN_SYATEKI_MAN,
    /* 0x00C2 */ ACTOR_EN_TANA,
    /* 0x00C3 */ ACTOR_EN_NB,
    /* 0x00C4 */ ACTOR_BOSS_MO,
    /* 0x00C5 */ ACTOR_EN_SB,
    /* 0x00C6 */ ACTOR_EN_BIGOKUTA,
    /* 0x00C7 */ ACTOR_EN_KAREBABA,
    /* 0x00C8 */ ACTOR_BG_BDAN_OBJECTS,
    /* 0x00C9 */ ACTOR_DEMO_SA,
    /* 0x00CA */ ACTOR_DEMO_GO,
    /* 0x00CB */ ACTOR_EN_IN,
    /* 0x00CC */ ACTOR_EN_TR,
    /* 0x00CD */ ACTOR_BG_SPOT16_BOMBSTONE,
    /* 0x00CE */ ACTOR_UNSET_CE,
    /* 0x00CF */ ACTOR_BG_HIDAN_KOWARERUKABE,
    /* 0x00D0 */ ACTOR_BG_BOMBWALL,
    /* 0x00D1 */ ACTOR_BG_SPOT08_ICEBLOCK,
    /* 0x00D2 */ ACTOR_EN_RU2,
    /* 0x00D3 */ ACTOR_OBJ_DEKUJR,
    /* 0x00D4 */ ACTOR_BG_MIZU_UZU,
    /* 0x00D5 */ ACTOR_BG_SPOT06_OBJECTS,
    /* 0x00D6 */ ACTOR_BG_ICE_OBJECTS,
    /* 0x00D7 */ ACTOR_BG_HAKA_WATER,
    /* 0x00D8 */ ACTOR_UNSET_D8,
    /* 0x00D9 */ ACTOR_EN_MA2,
    /* 0x00DA */ ACTOR_EN_BOM_CHU,
    /* 0x00DB */ ACTOR_EN_HORSE_GAME_CHECK,
    /* 0x00DC */ ACTOR_BOSS_TW,
    /* 0x00DD */ ACTOR_EN_RR,
    /* 0x00DE */ ACTOR_EN_BA,
    /* 0x00DF */ ACTOR_EN_BX,
    /* 0x00E0 */ ACTOR_EN_ANUBICE,
    /* 0x00E1 */ ACTOR_EN_ANUBICE_FIRE,
    /* 0x00E2 */ ACTOR_BG_MORI_HASHIGO,
    /* 0x00E3 */ ACTOR_BG_MORI_HASHIRA4,
    /* 0x00E4 */ ACTOR_BG_MORI_IDOMIZU,
    /* 0x00E5 */ ACTOR_BG_SPOT16_DOUGHNUT,
    /* 0x00E6 */ ACTOR_BG_BDAN_SWITCH,
    /* 0x00E7 */ ACTOR_EN_MA1,
    /* 0x00E8 */ ACTOR_BOSS_GANON,
    /* 0x00E9 */ ACTOR_BOSS_SST,
    /* 0x00EA */ ACTOR_UNSET_EA,
    /* 0x00EB */ ACTOR_UNSET_EB,
    /* 0x00EC */ ACTOR_EN_NY,
    /* 0x00ED */ ACTOR_EN_FR,
    /* 0x00EE */ ACTOR_ITEM_SHIELD,
    /* 0x00EF */ ACTOR_BG_ICE_SHELTER,
    /* 0x00F0 */ ACTOR_EN_ICE_HONO,
    /* 0x00F1 */ ACTOR_ITEM_OCARINA,
    /* 0x00F2 */ ACTOR_UNSET_F2,
    /* 0x00F3 */ ACTOR_UNSET_F3,
    /* 0x00F4 */ ACTOR_MAGIC_DARK,
    /* 0x00F5 */ ACTOR_DEMO_6K,
    /* 0x00F6 */ ACTOR_EN_ANUBICE_TAG,
    /* 0x00F7 */ ACTOR_BG_HAKA_GATE,
    /* 0x00F8 */ ACTOR_BG_SPOT15_SAKU,
    /* 0x00F9 */ ACTOR_BG_JYA_GOROIWA,
    /* 0x00FA */ ACTOR_BG_JYA_ZURERUKABE,
    /* 0x00FB */ ACTOR_UNSET_FB,
    /* 0x00FC */ ACTOR_BG_JYA_COBRA,
    /* 0x00FD */ ACTOR_BG_JYA_KANAAMI,
    /* 0x00FE */ ACTOR_FISHING,
    /* 0x00FF */ ACTOR_OBJ_OSHIHIKI,
    /* 0x0100 */ ACTOR_BG_GATE_SHUTTER,
    /* 0x0101 */ ACTOR_EFF_DUST,
    /* 0x0102 */ ACTOR_BG_SPOT01_FUSYA,
    /* 0x0103 */ ACTOR_BG_SPOT01_IDOHASHIRA,
    /* 0x0104 */ ACTOR_BG_SPOT01_IDOMIZU,
    /* 0x0105 */ ACTOR_BG_PO_SYOKUDAI,
    /* 0x0106 */ ACTOR_BG_GANON_OTYUKA,
    /* 0x0107 */ ACTOR_BG_SPOT15_RRBOX,
    /* 0x0108 */ ACTOR_BG_UMAJUMP,
    /* 0x0109 */ ACTOR_UNSET_109,
    /* 0x010A */ ACTOR_ARROW_FIRE,
    /* 0x010B */ ACTOR_ARROW_ICE,
    /* 0x010C */ ACTOR_ARROW_LIGHT,
    /* 0x010D */ ACTOR_UNSET_10D,
    /* 0x010E */ ACTOR_UNSET_10E,
    /* 0x010F */ ACTOR_ITEM_ETCETERA,
    /* 0x0110 */ ACTOR_OBJ_KIBAKO,
    /* 0x0111 */ ACTOR_OBJ_TSUBO,
    /* 0x0112 */ ACTOR_EN_WONDER_ITEM,
    /* 0x0113 */ ACTOR_EN_IK,
    /* 0x0114 */ ACTOR_DEMO_IK,
    /* 0x0115 */ ACTOR_EN_SKJ,
    /* 0x0116 */ ACTOR_EN_SKJNEEDLE,
    /* 0x0117 */ ACTOR_EN_G_SWITCH,
    /* 0x0118 */ ACTOR_DEMO_EXT,
    /* 0x0119 */ ACTOR_DEMO_SHD,
    /* 0x011A */ ACTOR_EN_DNS,
    /* 0x011B */ ACTOR_ELF_MSG,
    /* 0x011C */ ACTOR_EN_HONOTRAP,
    /* 0x011D */ ACTOR_EN_TUBO_TRAP,
    /* 0x011E */ ACTOR_OBJ_ICE_POLY,
    /* 0x011F */ ACTOR_BG_SPOT03_TAKI,
    /* 0x0120 */ ACTOR_BG_SPOT07_TAKI,
    /* 0x0121 */ ACTOR_EN_FZ,
    /* 0x0122 */ ACTOR_EN_PO_RELAY,
    /* 0x0123 */ ACTOR_BG_RELAY_OBJECTS,
    /* 0x0124 */ ACTOR_EN_DIVING_GAME,
    /* 0x0125 */ ACTOR_EN_KUSA,
    /* 0x0126 */ ACTOR_OBJ_BEAN,
    /* 0x0127 */ ACTOR_OBJ_BOMBIWA,
    /* 0x0128 */ ACTOR_UNSET_128,
    /* 0x0129 */ ACTOR_UNSET_129,
    /* 0x012A */ ACTOR_OBJ_SWITCH,
    /* 0x012B */ ACTOR_OBJ_ELEVATOR,
    /* 0x012C */ ACTOR_OBJ_LIFT,
    /* 0x012D */ ACTOR_OBJ_HSBLOCK,
    /* 0x012E */ ACTOR_EN_OKARINA_TAG,
    /* 0x012F */ ACTOR_EN_YABUSAME_MARK,
    /* 0x0130 */ ACTOR_EN_GOROIWA,
    /* 0x0131 */ ACTOR_EN_EX_RUPPY,
    /* 0x0132 */ ACTOR_EN_TORYO,
    /* 0x0133 */ ACTOR_EN_DAIKU,
    /* 0x0134 */ ACTOR_UNSET_134,
    /* 0x0135 */ ACTOR_EN_NWC,
    /* 0x0136 */ ACTOR_EN_BLKOBJ,
    /* 0x0137 */ ACTOR_ITEM_INBOX,
    /* 0x0138 */ ACTOR_EN_GE1,
    /* 0x0139 */ ACTOR_OBJ_BLOCKSTOP,
    /* 0x013A */ ACTOR_EN_SDA,
    /* 0x013B */ ACTOR_EN_CLEAR_TAG,
    /* 0x013C */ ACTOR_EN_NIW_LADY,
    /* 0x013D */ ACTOR_EN_GM,
    /* 0x013E */ ACTOR_EN_MS,
    /* 0x013F */ ACTOR_EN_HS,
    /* 0x0140 */ ACTOR_BG_INGATE,
    /* 0x0141 */ ACTOR_EN_KANBAN,
    /* 0x0142 */ ACTOR_EN_HEISHI3,
    /* 0x0143 */ ACTOR_EN_SYATEKI_NIW,
    /* 0x0144 */ ACTOR_EN_ATTACK_NIW,
    /* 0x0145 */ ACTOR_BG_SPOT01_IDOSOKO,
    /* 0x0146 */ ACTOR_EN_SA,
    /* 0x0147 */ ACTOR_EN_WONDER_TALK,
    /* 0x0148 */ ACTOR_BG_GJYO_BRIDGE,
    /* 0x0149 */ ACTOR_EN_DS,
    /* 0x014A */ ACTOR_EN_MK,
    /* 0x014B */ ACTOR_EN_BOM_BOWL_MAN,
    /* 0x014C */ ACTOR_EN_BOM_BOWL_PIT,
    /* 0x014D */ ACTOR_EN_OWL,
    /* 0x014E */ ACTOR_EN_ISHI,
    /* 0x014F */ ACTOR_OBJ_HANA,
    /* 0x0150 */ ACTOR_OBJ_LIGHTSWITCH,
    /* 0x0151 */ ACTOR_OBJ_MURE2,
    /* 0x0152 */ ACTOR_EN_GO,
    /* 0x0153 */ ACTOR_EN_FU,
    /* 0x0154 */ ACTOR_UNSET_154,
    /* 0x0155 */ ACTOR_EN_CHANGER,
    /* 0x0156 */ ACTOR_BG_JYA_MEGAMI,
    /* 0x0157 */ ACTOR_BG_JYA_LIFT,
    /* 0x0158 */ ACTOR_BG_JYA_BIGMIRROR,
    /* 0x0159 */ ACTOR_BG_JYA_BOMBCHUIWA,
    /* 0x015A */ ACTOR_BG_JYA_AMISHUTTER,
    /* 0x015B */ ACTOR_BG_JYA_BOMBIWA,
    /* 0x015C */ ACTOR_BG_SPOT18_BASKET,
    /* 0x015D */ ACTOR_UNSET_15D,
    /* 0x015E */ ACTOR_EN_GANON_ORGAN,
    /* 0x015F */ ACTOR_EN_SIOFUKI,
    /* 0x0160 */ ACTOR_EN_STREAM,
    /* 0x0161 */ ACTOR_UNSET_161,
    /* 0x0162 */ ACTOR_EN_MM,
    /* 0x0163 */ ACTOR_EN_KO,
    /* 0x0164 */ ACTOR_EN_KZ,
    /* 0x0165 */ ACTOR_EN_WEATHER_TAG,
    /* 0x0166 */ ACTOR_BG_SST_FLOOR,
    /* 0x0167 */ ACTOR_EN_ANI,
    /* 0x0168 */ ACTOR_EN_EX_ITEM,
    /* 0x0169 */ ACTOR_BG_JYA_IRONOBJ,
    /* 0x016A */ ACTOR_EN_JS,
    /* 0x016B */ ACTOR_EN_JSJUTAN,
    /* 0x016C */ ACTOR_EN_CS,
    /* 0x016D */ ACTOR_EN_MD,
    /* 0x016E */ ACTOR_EN_HY,
    /* 0x016F */ ACTOR_EN_GANON_MANT,
    /* 0x0170 */ ACTOR_EN_OKARINA_EFFECT,
    /* 0x0171 */ ACTOR_EN_MAG,
    /* 0x0172 */ ACTOR_DOOR_GERUDO,
    /* 0x0173 */ ACTOR_ELF_MSG2,
    /* 0x0174 */ ACTOR_DEMO_GT,
    /* 0x0175 */ ACTOR_EN_PO_FIELD,
    /* 0x0176 */ ACTOR_EFC_ERUPC,
    /* 0x0177 */ ACTOR_BG_ZG,
    /* 0x0178 */ ACTOR_EN_HEISHI4,
    /* 0x0179 */ ACTOR_EN_ZL3,
    /* 0x017A */ ACTOR_BOSS_GANON2,
    /* 0x017B */ ACTOR_EN_KAKASI,
    /* 0x017C */ ACTOR_EN_TAKARA_MAN,
    /* 0x017D */ ACTOR_OBJ_MAKEOSHIHIKI,
    /* 0x017E */ ACTOR_OCEFF_SPOT,
    /* 0x017F */ ACTOR_END_TITLE,
    /* 0x0180 */ ACTOR_UNSET_180,
    /* 0x0181 */ ACTOR_EN_TORCH,
    /* 0x0182 */ ACTOR_DEMO_EC,
    /* 0x0183 */ ACTOR_SHOT_SUN,
    /* 0x0184 */ ACTOR_EN_DY_EXTRA,
    /* 0x0185 */ ACTOR_EN_WONDER_TALK2,
    /* 0x0186 */ ACTOR_EN_GE2,
    /* 0x0187 */ ACTOR_OBJ_ROOMTIMER,
    /* 0x0188 */ ACTOR_EN_SSH,
    /* 0x0189 */ ACTOR_EN_STH,
    /* 0x018A */ ACTOR_OCEFF_WIPE,
    /* 0x018B */ ACTOR_OCEFF_STORM,
    /* 0x018C */ ACTOR_EN_WEIYER,
    /* 0x018D */ ACTOR_BG_SPOT05_SOKO,
    /* 0x018E */ ACTOR_BG_JYA_1FLIFT,
    /* 0x018F */ ACTOR_BG_JYA_HAHENIRON,
    /* 0x0190 */ ACTOR_BG_SPOT12_GATE,
    /* 0x0191 */ ACTOR_BG_SPOT12_SAKU,
    /* 0x0192 */ ACTOR_EN_HINTNUTS,
    /* 0x0193 */ ACTOR_EN_NUTSBALL,
    /* 0x0194 */ ACTOR_BG_SPOT00_BREAK,
    /* 0x0195 */ ACTOR_EN_SHOPNUTS,
    /* 0x0196 */ ACTOR_EN_IT,
    /* 0x0197 */ ACTOR_EN_GELDB,
    /* 0x0198 */ ACTOR_OCEFF_WIPE2,
    /* 0x0199 */ ACTOR_OCEFF_WIPE3,
    /* 0x019A */ ACTOR_EN_NIW_GIRL,
    /* 0x019B */ ACTOR_EN_DOG,
    /* 0x019C */ ACTOR_EN_SI,
    /* 0x019D */ ACTOR_BG_SPOT01_OBJECTS2,
    /* 0x019E */ ACTOR_OBJ_COMB,
    /* 0x019F */ ACTOR_BG_SPOT11_BAKUDANKABE,
    /* 0x01A0 */ ACTOR_OBJ_KIBAKO2,
    /* 0x01A1 */ ACTOR_EN_DNT_DEMO,
    /* 0x01A2 */ ACTOR_EN_DNT_JIJI,
    /* 0x01A3 */ ACTOR_EN_DNT_NOMAL,
    /* 0x01A4 */ ACTOR_EN_GUEST,
    /* 0x01A5 */ ACTOR_BG_BOM_GUARD,
    /* 0x01A6 */ ACTOR_EN_HS2,
    /* 0x01A7 */ ACTOR_DEMO_KEKKAI,
    /* 0x01A8 */ ACTOR_BG_SPOT08_BAKUDANKABE,
    /* 0x01A9 */ ACTOR_BG_SPOT17_BAKUDANKABE,
    /* 0x01AA */ ACTOR_UNSET_1AA,
    /* 0x01AB */ ACTOR_OBJ_MURE3,
    /* 0x01AC */ ACTOR_EN_TG,
    /* 0x01AD */ ACTOR_EN_MU,
    /* 0x01AE */ ACTOR_EN_GO2,
    /* 0x01AF */ ACTOR_EN_WF,
    /* 0x01B0 */ ACTOR_EN_SKB,
    /* 0x01B1 */ ACTOR_DEMO_GJ,
    /* 0x01B2 */ ACTOR_DEMO_GEFF,
    /* 0x01B3 */ ACTOR_BG_GND_FIREMEIRO,
    /* 0x01B4 */ ACTOR_BG_GND_DARKMEIRO,
    /* 0x01B5 */ ACTOR_BG_GND_SOULMEIRO,
    /* 0x01B6 */ ACTOR_BG_GND_NISEKABE,
    /* 0x01B7 */ ACTOR_BG_GND_ICEBLOCK,
    /* 0x01B8 */ ACTOR_EN_GB,
    /* 0x01B9 */ ACTOR_EN_GS,
    /* 0x01BA */ ACTOR_BG_MIZU_BWALL,
    /* 0x01BB */ ACTOR_BG_MIZU_SHUTTER,
    /* 0x01BC */ ACTOR_EN_DAIKU_KAKARIKO,
    /* 0x01BD */ ACTOR_BG_BOWL_WALL,
    /* 0x01BE */ ACTOR_EN_WALL_TUBO,
    /* 0x01BF */ ACTOR_EN_PO_DESERT,
    /* 0x01C0 */ ACTOR_EN_CROW,
    /* 0x01C1 */ ACTOR_DOOR_KILLER,
    /* 0x01C2 */ ACTOR_BG_SPOT11_OASIS,
    /* 0x01C3 */ ACTOR_BG_SPOT18_FUTA,
    /* 0x01C4 */ ACTOR_BG_SPOT18_SHUTTER,
    /* 0x01C5 */ ACTOR_EN_MA3,
    /* 0x01C6 */ ACTOR_EN_COW,
    /* 0x01C7 */ ACTOR_BG_ICE_TURARA,
    /* 0x01C8 */ ACTOR_BG_ICE_SHUTTER,
    /* 0x01C9 */ ACTOR_EN_KAKASI2,
    /* 0x01CA */ ACTOR_EN_KAKASI3,
    /* 0x01CB */ ACTOR_OCEFF_WIPE4,
    /* 0x01CC */ ACTOR_EN_EG,
    /* 0x01CD */ ACTOR_BG_MENKURI_NISEKABE,
    /* 0x01CE */ ACTOR_EN_ZO,
    /* 0x01CF */ ACTOR_OBJ_MAKEKINSUTA,
    /* 0x01D0 */ ACTOR_EN_GE3,
    /* 0x01D1 */ ACTOR_OBJ_TIMEBLOCK,
    /* 0x01D2 */ ACTOR_OBJ_HAMISHI,
    /* 0x01D3 */ ACTOR_EN_ZL4,
    /* 0x01D4 */ ACTOR_EN_MM2,
    /* 0x01D5 */ ACTOR_BG_JYA_BLOCK,
    /* 0x01D6 */ ACTOR_OBJ_WARP2BLOCK,
    /* 0x01D7 */ ACTOR_ID_MAX // originally "ACTOR_DLF_MAX"
} ActorID;

#endif
