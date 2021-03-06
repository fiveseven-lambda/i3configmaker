#include <stdio.h>

#define MOD "Mod4"

struct bind{
	char key[100];
	char command[100];
};

struct bind global[] = {
	{
		.key = MOD "+Return",
		.command = "exec alacritty"
	}, {
		.key = MOD "+Shift+space",
		.command = "exec rofi -show run"
	}, {
		.key = MOD "+Delete",
		.command = "kill"
	}, {
		.key = MOD "+Shift+f",
		.command = "fullscreen toggle"
	}, {
		.key = MOD "+Print",
		.command = "exec gm import -window root $(date \"+screenshot/%Y%m%d-%H%M%S.png\")"
	}
};

struct mode{
	char name[100];
	char key[100];
	_Bool def;
	_Bool border;
	struct bind bind[100];
} mode[] = {
	{
		.name = "exit [e: exit] [r: restart] [w: reload]",
		.key = MOD "+Shift+e",
		.def = 0,
		.border = 0,
		.bind = {
			{
				.key = "e",
				.command = "exec killall mozc_server; exit"
			}, {
				.key = "r",
				.command = "restart"
			}, {
				.key = "w",
				.command = "reload"
			}, { .key = "" }
		}
	}, {
		.name = "layout [h: splith] [v: splitv] [t: tabbed] [s: stacking] [f: floating toggle]",
		.key = MOD "+l",
		.def = 1,
		.border = 0,
		.bind = {
			{
				.key = "h",
				.command = "layout splith"
			}, {
				.key = "v",
				.command = "layout splitv"
			}, {
				.key = "t",
				.command = "layout tabbed"
			}, {
				.key = "s",
				.command = "layout stacking"
			}, {
				.key = "f",
				.command = "floating toggle"
			}, { .key = "" }
		}
	}, {
		.name = "split [h: horizontal] [v: vertical]",
		.key = MOD "+s",
		.def = 1,
		.border = 0,
		.bind = {
			{
				.key = "h",
				.command = "split horizontal"
			}, {
				.key = "v",
				.command = "split vertical"
			}, { .key = "" }
		}
	}, {
		.name = "focus [h: left] [j: down] [k: up] [l: right] [p: parent] [c: child] [f: floating]",
		.key = MOD "+f",
		.def = 0,
		.border = 1,
		.bind = {
			{
				.key = "h",
				.command = "border pixel 1; focus left; border normal"
			}, {
				.key = "j",
				.command = "border pixel 1; focus down; border normal"
			}, {
				.key = "k",
				.command = "border pixel 1; focus up; border normal"
			}, {
				.key = "l",
				.command = "border pixel 1; focus right; border normal"
			}, {
				.key = "p",
				.command = "border pixel 1; focus parent"
			}, {
				.key = "c",
				.command = "focus child; border normal"
			}, {
				.key = "f",
				.command = "border pixel 1; focus mode_toggle; border normal"
			}, { .key = "" }
		}
	}, {
		.name = "move [h: left] [j: down] [k: up] [l: right] [c: center] [m: mouse]",
		.key = MOD "+m",
		.def = 0,
		.border = 1,
		.bind = {
			{
				.key = "h",
				.command = "move left"
			}, {
				.key = "Shift+h",
				.command = "move left 50 px"
			}, {
				.key = "j",
				.command = "move down"
			}, {
				.key = "Shift+j",
				.command = "move down 50 px"
			}, {
				.key = "k",
				.command = "move up"
			}, {
				.key = "Shift+k",
				.command = "move up 50 px"
			}, {
				.key = "l",
				.command = "move right"
			}, {
				.key = "Shift+l",
				.command = "move right 50 px"
			}, {
				.key = "c",
				.command = "move absolute position center"
			}, {
				.key = "m",
				.command = "move position mouse"
			}, { .key = "" }
		}
	}, {
		.name = "resize [h: shrink width] [j: grow height] [k: shrink height] [l: grow width]",
		.key = MOD "+r",
		.def = 0,
		.border = 1,
		.bind = {
			{
				.key = "h",
				.command = "resize shrink width"
			}, {
				.key = "Shift+h",
				.command = "resize shrink width 50 px"
			}, {
				.key = "j",
				.command = "resize grow height"
			}, {
				.key = "Shift+j",
				.command = "resize grow height 50 px"
			}, {
				.key = "k",
				.command = "resize shrink height"
			}, {
				.key = "Shift+k",
				.command = "resize shrink height 50 px"
			}, {
				.key = "l",
				.command = "resize grow width"
			}, {
				.key = "Shift+l",
				.command = "resize grow width 50 px"
			}, { .key = "" }
		}
	}, {
		.name = "workspace",
		.key = MOD "+w",
		.def = 1,
		.border = 0,
		.bind = {
			{ .key = "" }
		}
	}
};

int main(){
	printf("bar{\nstatus_command i3status\n}\ndefault_border pixel 1\n");
	for(int i = 0; i < sizeof global / sizeof global[0]; ++i){
		printf("bindsym %s %s\n", global[i].key, global[i].command);
	}
	for(int i = 0; i < sizeof mode / sizeof mode[0]; ++i){
		printf("bindsym %s ", mode[i].key);
		if(mode[i].border) printf("border normal; ");
		printf("mode \"%s\"\n", mode[i].name);
	}
	for(int i = 0; i < sizeof mode / sizeof mode[0]; ++i){
		printf("mode \"%s\"{\n", mode[i].name);
		printf("\tbindsym Return ");
		if(mode[i].border) printf("border pixel 1; ");
		printf("mode \"default\"\n");
		for(int j = 0; mode[i].bind[j].key[0]; ++j){
			printf("\tbindsym %s %s", mode[i].bind[j].key, mode[i].bind[j].command);
			if(mode[i].def) printf("; mode \"default\"");
			printf("\n");
		}
		if(!mode[i].bind[0].key[0]){
			for(int j = 0; j <= 9; ++j){
				printf("\tbindsym %d workspace %d", j, j);
				if(mode[i].def) printf("; mode \"default\"");
				printf("\n");
				printf("\tbindsym Shift+%d move container to workspace %d; workspace %d", j, j, j);
				if(mode[i].def) printf("; mode \"default\"");
				printf("\n");
			}
			for(char j = 'A'; j <= 'Z'; ++j){
				printf("\tbindsym %c workspace %c", j, j);
				if(mode[i].def) printf("; mode \"default\"");
				printf("\n");
				printf("\tbindsym Shift+%c move container to workspace %c; workspace %c", j, j, j);
				if(mode[i].def) printf("; mode \"default\"");
				printf("\n");
			}
		}
		for(int j = 0; j < sizeof mode / sizeof mode[0]; ++j){
			if(i != j){
				printf("\tbindsym %s ", mode[j].key);
				if(!mode[i].border){
					if(mode[j].border) printf("border normal; ");
				}else{
					if(!mode[j].border) printf("border pixel 1; ");
				}
				printf("mode \"%s\"\n", mode[j].name);
			}
		}
		printf("}\n");
	}
}
