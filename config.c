#include <stdio.h>
#include <string.h>

const char mod[] = "Mod4";

struct sym{
	_Bool mod;
	_Bool def;
	char key[100];
	char command[100];
};

void bindsym(struct sym *s){
	printf("bindsym ");
	if(s->mod) printf("%s+", mod);
	printf("%s %s", s->key, s->command);
	if(s->def) printf("; mode \"default\"");
	putchar('\n');
}

struct sym global[] = {
	{
		.mod = 1,
		.key = "Return",
		.command = "exec terminator"
	},{
		.mod = 1,
		.key = "Shift+space",
		.command = "exec rofi -show run"
	},{
		.mod = 1,
		.key = "Delete",
		.command = "kill"
	}
};

struct mode{
	char name[1000];
	char key[100];
	_Bool description;
	struct sym sym[100];
};

void desc(struct mode *m){
	for(int i = 0; m->sym[i].key[0]; ++i) sprintf(m->name + strlen(m->name), " [%s : %s]", m->sym[i].key, m->sym[i].command);
}

struct mode mode[] = {
	{
		.name = "exit",
		.key = "Shift+e",
		.description = 1,
		.sym = {
			{
				.key = "e",
				.command = "exec killall mozc_server; exit"
			},{
				.key = "r",
				.command = "restart"
			},{
				.key = "w",
				.command = "reload"
			}
		}
	},{
		.name = "split",
		.key = "s",
		.description = 1,
		.sym = {
			{
				.def = 1,
				.key = "v",
				.command = "split vertical"
			},{
				.def = 1,
				.key = "h",
				.command = "split horizontal"
			},{
				.def = 1,
				.key = "t",
				.command = "split toggle"
			}
		}
	},{
		.name = "layout",
		.key = "l",
		.description = 1,
		.sym = {
			{
				.def = 1,
				.key = "d",
				.command = "layout default"
			},{
				.def = 1,
				.key = "t",
				.command = "layout tabbed"
			},{
				.def = 1,
				.key = "s",
				.command = "layout stacking"
			},{
				.def = 1,
				.key = "v",
				.command = "layout splitv"
			},{
				.def = 1,
				.key = "h",
				.command = "layout splith"
			},{
				.def = 1,
				.key = "f",
				.command = "fullscreen toggle"
			},{
				.def = 1,
				.key = "Shift+f",
				.command = "floating toggle"
			}
		}
	},{
		.name = "focus",
		.key = "f",
		.description = 1,
		.sym = {
			{
				.def = 1,
				.key = "h",
				.command = "focus left"
			},{
				.def = 1,
				.key = "j",
				.command = "focus down"
			},{
				.def = 1,
				.key = "k",
				.command = "focus up"
			},{
				.def = 1,
				.key = "l",
				.command = "focus right"
			},{
				.def = 1,
				.key = "p",
				.command = "focus parent"
			},{
				.def = 1,
				.key = "f",
				.command = "focus mode_toggle"
			}
		}
	},{
		.name = "move",
		.key = "m",
		.description = 1,
		.sym = {
			{
				.def = 1,
				.key = "h",
				.command = "move left"
			},{
				.def = 1,
				.key = "j",
				.command = "move down"
			},{
				.def = 1,
				.key = "k",
				.command = "move up"
			},{
				.def = 1,
				.key = "l",
				.command = "move right"
			},{
				.def = 1,
				.key = "c",
				.command = "move absolute position center"
			},{
				.def = 1,
				.key = "m",
				.command = "move position mouse"
			}
		}
	},{
		.name = "sticky",
		.key = "Shift+s",
		.description = 1,
		.sym = {
			{
				.def = 1,
				.key = "e",
				.command = "sticky enable"
			},{
				.def = 1,
				.key = "d",
				.command = "sticky disable"
			},{
				.def = 1,
				.key = "t",
				.command = "sticky toggle"
			}
		}
	},{
		.name = "resize",
		.key = "r",
		.description = 1,
		.sym = {
			{
				.def = 1,
				.key = "h",
				.command = "resize shrink width"
			},{
				.def = 1,
				.key = "j",
				.command = "resize grow height"
			},{
				.def = 1,
				.key = "k",
				.command = "resize shrink height"
			},{
				.def = 1,
				.key = "l",
				.command = "resize grow width"
			}
		}
	},{
		.name = "border",
		.key = "b",
		.description = 1,
		.sym = {
			{
				.def = 1,
				.key = "n",
				.command = "border normal"
			},{
				.def = 1,
				.key = "p",
				.command = "border pixel"
			},{
				.def = 1,
				.key = "Shift+n",
				.command = "border none"
			}
		}
	},{
		.name = "workspace",
		.key = "w",
		.description = 0,
	}
};

void switch_to_mode(struct mode *m){
	printf("bindsym %s+%s mode \"%s\"\n", mod, m->key, m->name);
}

void set_workspace(){
	for(int i = 0; i < sizeof mode / sizeof mode[0]; ++i) if(!strcmp(mode[i].name, "workspace")){
		for(int j = 0; j < 10; ++j){
			sprintf(mode[i].sym[j * 2].key, "%d", j);
			sprintf(mode[i].sym[j * 2].command, "workspace %d; mode \"default\"", j);
			sprintf(mode[i].sym[j * 2 + 1].key, "Shift+%d", j);
			sprintf(mode[i].sym[j * 2 + 1].command, "move container to workspace %d; workspace %d; mode \"default\"", j, j);
		}
		for(int j = 0; j < 26; ++j){
			sprintf(mode[i].sym[j * 2 + 20].key, "%c", 'A' + j);
			sprintf(mode[i].sym[j * 2 + 20].command, "workspace %c; mode \"default\"", 'A' + j);
			sprintf(mode[i].sym[j * 2 + 21].key, "Shift+%c", 'A' + j);
			sprintf(mode[i].sym[j * 2 + 21].command, "move container to workspace %c; workspace %c; mode \"default\"", 'A' + j, 'A' + j);
		}
	}
}

void print_mode(struct mode *m){
	printf("mode \"%s\"{\nbindsym Return mode \"default\"\n", m->name);
	for(int i = 0; i < sizeof global / sizeof global[0]; ++i) bindsym(global + i);
	for(int i = 0; i < sizeof mode / sizeof mode[0]; ++i) if(mode + i != m) switch_to_mode(mode + i);
	for(int i = 0; m->sym[i].key[0]; ++i) bindsym(m->sym + i);
	printf("}\n");
}

int main(){
	for(int i = 0; i < sizeof global / sizeof global[0]; ++i) bindsym(global + i);
	printf("bar{\nstatus_command i3status\n}\n");
	printf("default_border pixel 1\n");
	set_workspace();
	for(int i = 0; i < sizeof mode / sizeof mode[0]; ++i) if(mode[i].description) desc(mode + i);
	for(int i = 0; i < sizeof mode / sizeof mode[0]; ++i) switch_to_mode(mode + i);
	for(int i = 0; i < sizeof mode / sizeof mode[0]; ++i) print_mode(mode + i);
}
