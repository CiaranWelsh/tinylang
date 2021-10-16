// A Bison parser, made by GNU Bison 3.7.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "Parser.h"




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 4 ".\\tinylang.yy"
namespace tinylang {
#line 118 "tinylang.tab.cc"

  /// Build a parser object.
  Parser::Parser ()
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr)
#else

#endif
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
  {
    switch (this->kind ())
    {
      default:
        break;
    }

  }



  template <typename Base>
  Parser::symbol_kind_type
  Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      default:
        break;
    }

  }

  // by_kind.
  Parser::by_kind::by_kind ()
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  Parser::by_kind::by_kind (by_kind&& that)
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  Parser::by_kind::by_kind (const by_kind& that)
    : kind_ (that.kind_)
  {}

  Parser::by_kind::by_kind (token_kind_type t)
    : kind_ (yytranslate_ (t))
  {}

  void
  Parser::by_kind::clear ()
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  Parser::symbol_kind_type
  Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }

  Parser::symbol_kind_type
  Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state))
  {
    switch (that.kind ())
    {
      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s)
  {
    switch (that.kind ())
    {
      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      default:
        break;
    }

    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      default:
        break;
    }

    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YYUSE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {

#line 584 "tinylang.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        std::string msg = YY_("syntax error");
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

#if YYDEBUG || 0
  const char *
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0





  const signed char Parser::yypact_ninf_ = -68;

  const signed char Parser::yytable_ninf_ = -41;

  const signed char
  Parser::yypact_[] =
  {
     -28,     4,    16,    15,   -68,    -7,    48,    50,    21,    -7,
      13,    47,    41,    57,    59,    50,    61,    43,    21,    52,
     -68,    50,    50,   -68,    51,   -68,    49,   -68,    55,    60,
       0,    44,   -68,   -68,    62,   -68,    42,     2,    64,    70,
     -68,    67,    42,    27,    42,   -68,    73,   -68,   -68,     1,
     -68,   -68,   -68,   -68,    74,    65,     9,   -68,    66,    76,
      50,    21,    77,    70,    53,   -68,   -68,    68,     0,    42,
      30,   -68,    57,   -68,   -68,   -68,   -68,   -68,   -68,    42,
     -68,    42,     9,   -68,    14,     6,    72,    80,     2,    82,
      88,    50,   -68,     0,     0,   -68,   -68,    75,   -68,    86,
     -68,   -68,    78,   -68,   -68,   -68,   -68,     9,   -68,   -68,
     -68,   -68,   -68,     9,   -68,    70,   -68,   -68,    70,   -68,
     -68,    79,    71,   -68,    42,   -68,   -68,   -68,   -68,   -68,
       0,    81,   -68,   -68,   -68,   -68
  };

  const signed char
  Parser::yydefact_[] =
  {
       0,     0,     0,     0,     1,     3,     0,     0,     8,     3,
       0,    79,     0,    13,     0,    15,     0,    27,     8,     0,
       4,     0,     0,     6,     0,    10,    18,    11,     0,     0,
       0,     0,     9,    12,     0,    78,    59,    20,     0,     0,
       2,    77,    59,    59,    59,    28,    30,    33,    34,    36,
       7,     5,    60,    61,     0,    49,     0,    24,     0,     0,
       0,     8,     0,     0,     0,    35,    41,     0,     0,    59,
      59,    32,    13,    50,    51,    52,    54,    53,    55,    59,
      72,    59,     0,    56,    58,    66,    36,    25,    20,     0,
       0,    15,    76,     0,     0,    29,    31,     0,    39,    47,
      14,    48,     0,    74,    62,    63,    64,     0,    67,    68,
      71,    69,    70,     0,    75,     0,    19,    21,     0,    17,
      16,    43,     0,    37,    59,    73,    57,    65,    26,    22,
       0,     0,    45,    46,    44,    42
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -68,   -68,    92,   -68,    45,    84,   -68,    31,    19,   -68,
     -68,    17,   -68,   -68,   -68,   -68,   -67,   -68,    18,   -68,
     -68,   -68,   -68,   -68,   -17,   -34,   -68,    32,     5,   -68,
     -68,     3,   -68,    33,   -39,    -3
  };

  const short
  Parser::yydefgoto_[] =
  {
      -1,     2,     8,     9,    16,    17,    18,    25,    27,    19,
      38,    58,    59,    60,   116,    31,    45,    46,    71,    97,
      65,    47,   131,    48,    98,    99,    79,    55,    83,    56,
     107,    84,   113,    85,    49,    28
  };

  const short
  Parser::yytable_[] =
  {
      62,    95,    54,    41,    12,   -23,     1,     3,    64,    66,
      67,    69,    41,    80,   108,   109,     4,    86,    34,    35,
     104,   105,    70,     6,    92,     7,   121,   122,     5,   110,
      81,    42,   111,    52,    53,    96,    52,    53,    43,   112,
     -40,    44,    57,    86,    82,    21,    13,   102,    52,    53,
     106,    10,   -38,    11,    23,   -40,   -40,    89,    14,    22,
      24,    15,    26,   134,    29,    33,    36,    30,    86,    39,
      37,    40,    50,    41,    86,    51,   128,    61,    63,   129,
      73,    74,    75,    76,    77,    78,    68,    72,    87,    88,
      91,   119,    93,    70,   115,    94,   118,   123,   124,   132,
     125,    20,    32,   100,   114,   117,    90,   133,   130,   135,
     120,   101,   126,     0,     0,   103,   127
  };

  const short
  Parser::yycheck_[] =
  {
      39,    68,    36,     3,     7,     3,    34,     3,    42,    43,
      44,    10,     3,     4,     8,     9,     0,    56,    21,    22,
       6,     7,    21,    30,    63,    32,    93,    94,    13,    23,
      21,    31,    26,     6,     7,    69,     6,     7,    38,    33,
      13,    41,    40,    82,    35,    32,    25,    81,     6,     7,
      36,     3,    22,     3,    13,    28,    29,    60,    37,    12,
       3,    40,     3,   130,     3,    13,    15,    24,   107,    14,
      21,    11,    28,     3,   113,    13,   115,    13,    11,   118,
      15,    16,    17,    18,    19,    20,    13,    13,    22,    13,
      13,     3,    39,    21,    14,    27,    14,    22,    12,    28,
      22,     9,    18,    72,    86,    88,    61,   124,    29,    28,
      91,    79,   107,    -1,    -1,    82,   113
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    34,    43,     3,     0,    13,    30,    32,    44,    45,
       3,     3,    77,    25,    37,    40,    46,    47,    48,    51,
      44,    32,    12,    13,     3,    49,     3,    50,    77,     3,
      24,    57,    47,    13,    77,    77,    15,    21,    52,    14,
      11,     3,    31,    38,    41,    58,    59,    63,    65,    76,
      28,    13,     6,     7,    67,    69,    71,    40,    53,    54,
      55,    13,    76,    11,    67,    62,    67,    67,    13,    10,
      21,    60,    13,    15,    16,    17,    18,    19,    20,    68,
       4,    21,    35,    70,    73,    75,    76,    22,    13,    77,
      46,    13,    76,    39,    27,    58,    67,    61,    66,    67,
      49,    69,    67,    75,     6,     7,    36,    72,     8,     9,
      23,    26,    33,    74,    60,    14,    56,    53,    14,     3,
      50,    58,    58,    22,    12,    22,    70,    73,    76,    76,
      29,    64,    28,    66,    58,    28
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    42,    43,    44,    44,    45,    45,    46,    47,    47,
      48,    48,    48,    49,    49,    50,    50,    51,    52,    52,
      53,    53,    54,    55,    55,    56,    56,    57,    57,    58,
      58,    59,    59,    59,    59,    59,    60,    60,    61,    61,
      62,    62,    63,    64,    64,    65,    66,    66,    67,    67,
      68,    68,    68,    68,    68,    68,    69,    70,    70,    71,
      71,    71,    72,    72,    72,    73,    73,    74,    74,    74,
      74,    74,    75,    75,    75,    75,    76,    76,    77,    77
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     7,     0,     2,     5,     3,     3,     0,     2,
       2,     2,     2,     0,     5,     0,     5,     6,     0,     4,
       0,     3,     4,     0,     1,     0,     2,     0,     2,     3,
       1,     3,     2,     1,     1,     2,     0,     3,     0,     1,
       0,     1,     6,     0,     2,     5,     3,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     2,     3,     1,     0,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     3,     2,     2,     3,     1,     3,     1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "identifier",
  "integer_literal", "string_literal", "PLUS", "MINUS", "STAR", "SLASH",
  "COLONEQUAL", "PERIOD", "COMMA", "SEMI", "COLON", "EQUAL", "HASH",
  "LESS", "GREATER", "LESSEQUAL", "GREATEREQUAL", "L_PAREN", "R_PAREN",
  "AND", "BEGIN", "CONST", "DIV", "DO", "END", "ELSE", "FROM", "IF",
  "IMPORT", "MOD", "MODULE", "NOT", "OR", "PROCEDURE", "RETURN", "THEN",
  "VAR", "WHILE", "$accept", "compilationUnit", "imports", "import",
  "block", "declarations", "declaration", "constantDeclaration",
  "variableDeclaration", "procedureDeclaration", "formalParameters",
  "formalParameterList", "formalParameter", "varParam", "resultType",
  "blockBody", "statementSequence", "statement", "actualParams",
  "actualParamList", "returnExpr", "ifStatement", "elseStatement",
  "whileStatement", "expList", "expression", "relation",
  "prefixedExpression", "simpleExpression", "prefixOperator",
  "addOperator", "term", "mulOperator", "factor", "qualident", "identList", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const signed char
  Parser::yyrline_[] =
  {
       0,    20,    20,    21,    21,    23,    24,    25,    26,    26,
      28,    29,    30,    32,    33,    35,    36,    38,    41,    41,
      43,    43,    45,    46,    46,    47,    47,    48,    48,    50,
      50,    52,    53,    54,    54,    54,    55,    55,    56,    56,
      57,    57,    59,    62,    62,    64,    66,    66,    68,    69,
      71,    71,    71,    71,    71,    71,    72,    74,    74,    75,
      75,    75,    76,    76,    76,    77,    77,    78,    78,    78,
      78,    78,    80,    80,    80,    81,    82,    82,    83,    83
  };

  void
  Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  Parser::symbol_kind_type
  Parser::yytranslate_ (int t)
  {
    return static_cast<symbol_kind_type> (t);
  }

#line 4 ".\\tinylang.yy"
} // tinylang
#line 983 "tinylang.tab.cc"

