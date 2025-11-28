#ifndef GAME_H
#define GAME_H
#include "pieces.h"

// اللاعب
typedef struct {
    Color color;                // لون اللاعب
    Piece pieces[16];           // الـ16 قطعة
    
    // حالة اللعب (خاصة باللاعب فقط)
    int is_in_check;            // في كش؟
    int can_castle_kingside;    // يقدر يعمل تبييت يمين؟
    int can_castle_queenside;   // يقدر يعمل تبييت شمال؟
    
    // إحصائيات (مفيدة للعرض)
    int total_pieces;           // عدد القطع المتبقية
    int total_captured;         // عدد القطع المأخوذة
    
    // ✅ شلنا: en_passant, halfmove_clock, fullmove_number, total_possible_moves
} Player;

#endif