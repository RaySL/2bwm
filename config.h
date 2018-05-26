#define MOD             XCB_MOD_MASK_4
#define CURSOR_POSITION MIDDLE
#define LOOK_INTO 	"WM_NAME"
#define WORKSPACES      5

static const bool resize_by_line = true;
static const bool inverted_colors = false;
static const float resize_keep_aspect_ratio = 1.05;

static const char *ignore_names[] = { "bar" };
static const char *menucmd[]      = { "", NULL };
static const char *terminal[]     = { "st", NULL };
static const char *rofi[]         = { "rofi", "-show", "drun", NULL };
//static const char *draw[]         = { "bash", "~/.bin/draw", NULL };

static const uint16_t movements[] = { 
	16,  //step slow
	32, //step normal
	16,  //mouse slow
	32  //mouse normal
};

static const uint8_t offsets[] = { 
	0, //offsetx
	0, //offsety
	0, //maxwidth
	0  //maxheight
};

// Current colors are in .Xresources
static const char *colors[] = {
	"#000000", //focuscol
	"#000000", //unfocuscol
	"#000000", //fixedcol
	"#000000", //unkilcol
	"#000000", //fixedunkilcol
	"#000000", //outerbordercol
	"#000000"  //emptycol
};
//static const char *colors[] = {"#ac8d6e","#607a86","#a66959","#60867f","#8a757e","#20292d","#20292d"};
static const uint8_t borders[] = { 
	5, //outer border size
	7, //full border size
	0, //magnet border size
	7  //resize border size
};

static void halfandcentered(const Arg *arg)
{
	Arg arg2 = {.i=TWOBWM_MAXHALF_VERTICAL_LEFT};
	maxhalf(&arg2);
	Arg arg3 = {.i=TWOBWM_TELEPORT_CENTER};
	teleport(&arg3);
}

static void killandfocus(const Arg *arg)
{
	Arg arg2 = {.i=TWOBWM_FOCUS_PREVIOUS};
	deletewin(&arg2);
	Arg arg3 = {.i=TWOBWM_FOCUS_PREVIOUS};
	focusnext(&arg3);
}

/* Doesn't work as wanted
static void changeandfocus(const Arg *arg)
{
	changeworkspace(arg);
	Arg arg2 = {.i=TWOBWM_FOCUS_PREVIOUS};
	focusnext(&arg2);
}
*/

#define DESKTOPCHANGE(K,N) \
    {  MOD ,                   K,             changeworkspace,     {.i=N} }, \
    {  MOD | SHIFT,            K,             sendtoworkspace,     {.i=N} },

static key keys[] = {
    /* modifier                key            function             argument */
    
    // Focus to next/previous window
    {  MOD,                    XK_Tab,        focusnext,           {.i = TWOBWM_FOCUS_NEXT} },
    {  MOD | SHIFT,            XK_Tab,        focusnext,           {.i = TWOBWM_FOCUS_PREVIOUS} },
    // Kill a window
    {  MOD,                    XK_q,          killandfocus,        {.i = 0} },
    // Resize a window
    {  MOD | SHIFT,            XK_Up,         resizestep,          {.i = TWOBWM_RESIZE_UP} },
    {  MOD | SHIFT,            XK_Down,       resizestep,          {.i = TWOBWM_RESIZE_DOWN} },
    {  MOD | SHIFT,            XK_Right,      resizestep,          {.i = TWOBWM_RESIZE_RIGHT} },
    {  MOD | SHIFT,            XK_Left,       resizestep,          {.i = TWOBWM_RESIZE_LEFT} },
    {  MOD | SHIFT,            XK_k,          resizestep,          {.i = TWOBWM_RESIZE_UP} },
    {  MOD | SHIFT,            XK_j,          resizestep,          {.i = TWOBWM_RESIZE_DOWN} },
    {  MOD | SHIFT,            XK_l,          resizestep,          {.i = TWOBWM_RESIZE_RIGHT} },
    {  MOD | SHIFT,            XK_h,          resizestep,          {.i = TWOBWM_RESIZE_LEFT} },
    // Move a window
    {  MOD,                    XK_Up,         movestep,            {.i = TWOBWM_MOVE_UP} },
    {  MOD,                    XK_Down,       movestep,            {.i = TWOBWM_MOVE_DOWN} },
    {  MOD,                    XK_Right,      movestep,            {.i = TWOBWM_MOVE_RIGHT} },
    {  MOD,                    XK_Left,       movestep,            {.i = TWOBWM_MOVE_LEFT} },
		{  MOD,                    XK_k,          movestep,            {.i = TWOBWM_MOVE_UP} },
    {  MOD,                    XK_j,       	  movestep,            {.i = TWOBWM_MOVE_DOWN} },
    {  MOD,                    XK_l,      	  movestep,            {.i = TWOBWM_MOVE_RIGHT} },
    {  MOD,                    XK_h,       	  movestep,            {.i = TWOBWM_MOVE_LEFT} },
    
    // Teleport the window to an area of the screen.
    // Center:
    {  MOD,                    XK_g,          teleport,            {.i = TWOBWM_TELEPORT_CENTER} },
    // Center y:
    {  MOD | SHIFT,            XK_g,          teleport,            {.i = TWOBWM_TELEPORT_CENTER_Y} },
    // Center x:
    {  MOD | CONTROL,          XK_g,          teleport,            {.i = TWOBWM_TELEPORT_CENTER_X} },
    // Top left:
    {  MOD,                    XK_y,          teleport,            {.i = TWOBWM_TELEPORT_TOP_LEFT} },
    // Top right:
    {  MOD,                    XK_u,          teleport,            {.i = TWOBWM_TELEPORT_TOP_RIGHT} },
    // Bottom left:
    {  MOD,                    XK_b,          teleport,            {.i = TWOBWM_TELEPORT_BOTTOM_LEFT} },
    // Bottom right:
    {  MOD,                    XK_n,          teleport,            {.i = TWOBWM_TELEPORT_BOTTOM_RIGHT} },
    // Resize while keeping the window aspect
    {  MOD,                    XK_o,          resizestep_aspect,   {.i = TWOBWM_RESIZE_KEEP_ASPECT_GROW} },
    {  MOD,                    XK_p,          resizestep_aspect,   {.i = TWOBWM_RESIZE_KEEP_ASPECT_SHRINK} },
    // Full screen window without borders
    {  MOD,                    XK_f,          maximize,            {.i = TWOBWM_FULLSCREEN} },
    // Maximize vertically
    //{  MOD ,                   XK_m,          maxvert_hor,         {.i = TWOBWM_MAXIMIZE_VERTICALLY} },
    // Maximize horizontally
    //{  MOD | SHIFT,            XK_m,          maxvert_hor,         {.i = TWOBWM_MAXIMIZE_HORIZONTALLY} },
    // Maximize and move
    // vertically left
    //{  MOD | SHIFT,            XK_y,          maxhalf,             {.i = TWOBWM_MAXHALF_VERTICAL_LEFT} },
    // vertically right
    //{  MOD | SHIFT,            XK_u,          maxhalf,             {.i = TWOBWM_MAXHALF_VERTICAL_RIGHT} },
    // horizontally left
    //{  MOD | SHIFT,            XK_b,          maxhalf,             {.i = TWOBWM_MAXHALF_HORIZONTAL_BOTTOM} },
    // horizontally right
    //{  MOD | SHIFT,            XK_n,          maxhalf,             {.i = TWOBWM_MAXHALF_HORIZONTAL_TOP} },
    // Raise or lower a window
    //{  MOD,                    XK_r,          raiseorlower,        {} },
    // Next/Previous workspace
    //{  MOD,                    XK_v,          nextworkspace,       {} },
    //{  MOD,                    XK_c,          prevworkspace,       {} },
    // Move to Next/Previous workspace
    //{  MOD | SHIFT,            XK_v,          sendtonextworkspace, {} },
    //{  MOD | SHIFT,            XK_c,          sendtoprevworkspace, {} },
    // Make the window unkillable
    {  MOD,                    XK_a,          unkillable,          {} },
    // Make the window appear always on top
    {  MOD,                    XK_t,          always_on_top,       {} },
    // Make the window stay on all workspaces
    {  MOD ,                   XK_space,      fix,                 {} },
    
    //Launch programs 
    {  MOD,                    XK_Return,     start,               {.com = terminal} },
    {  MOD,                    XK_d,          start,               {.com = rofi} },

		{  MOD,					   XK_Escape,	  twobwm_exit,		   {.i=0} },
    {  MOD, 				   XK_grave,      twobwm_restart,      {.i=0} },
   
		// Change current workspace
    DESKTOPCHANGE( XK_1, 0 )
    DESKTOPCHANGE( XK_2, 1 )
    DESKTOPCHANGE( XK_3, 2 )
		DESKTOPCHANGE( XK_4, 3 )
		DESKTOPCHANGE( XK_5, 4 )
};

static Button buttons[] = {
    { MOD,         XCB_BUTTON_INDEX_1,     mousemotion,     {.i = TWOBWM_MOVE}, false },
    { MOD,         XCB_BUTTON_INDEX_3,     mousemotion,     {.i = TWOBWM_RESIZE}, false },
};
