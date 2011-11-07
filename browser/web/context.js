function get_file_path(tr){
	if(tr.tagName=="DIV"){
		path = $(tr).find("input")[1].value;
		file = $(tr).find("input")[0].value;
	}else if(tr.tagName=="UL"){
		alert(tr.tagName);
	}else{
		tds = $(tr).find("td");
		file = tds[0].title;
		path = tds[1].title;
		type = tds[2].value;
	}
}

function delete_file(t){
	get_file_path(t);
	if(window.confirm("您确定要删除 '"+file+"' 吗?")){
		var ret = cef.plugin.shell2(path+file, "delete");
		refresh();
		info_or_error(ret, file, "删除");
	}
}
function copy_file(t){
	get_file_path(t);
	var ret = cef.plugin.shell2(path+file, "copy");
	info_or_error(ret, file, "复制");
}
function cut_file(t){
	get_file_path(t);
	var ret = cef.plugin.shell2(path+file, "cut");
	info_or_error(ret, file, "剪切");
}

function dblclick_file(target){
	get_file_path(target);
	var ret = cef.plugin.shellDefault(path+file);
	info_if_error(ret, file, "打开");
}


function dblclick_path(target){
	get_file_path(target);
	if(path.substr(0,1)=="\\"){
		file = path.substr(0,path.length-1);
		var ret = cef.plugin.shellDefault(file);
		info_if_error(ret, file, "打开");
	}else{
		var ret = cef.plugin.shellExplore(path+file);
		info_if_error(ret, path, "资源管理器");
	}
}

var context_menu_obj = {
				  menuStyle: {
					width : "150px"
				  },
				  itemStyle: {
				  },
				  itemHoverStyle: {
				  },
/* 
				  onShowMenu: function(e, menu) {
					if ($(e.target).parents().find("input")[0].value != 'dir') { //性能有问题
					  $('#paste', menu).remove();
					}
					return menu;
				  },
*/
                  onContextMenu : function(event, menu){
                                  var rowId = $(event.target).parent("tr").attr("id");
								  if(!has_row_selected(rowId)){
									grid_batch_unselect();
									$("#maintable").setSelection(rowId);
								  }
                                  return true;
                  },
				  bindings: {
					  'default': function(t,menuitem) {
					    get_file_path(t);
						var ret = cef.plugin.shellDefault(path+file);
						info_if_error(ret, file, menuitem.lastChild.data);
					  },
					  'openas': function(t,menuitem) {
					    get_file_path(t);
						var ret = cef.plugin.shell2(path+file,"openas");
						info_if_error(ret, file, menuitem.lastChild.data);
					  },
					  'explore': function(t,menuitem) {
					    get_file_path(t);
						var ret = cef.plugin.shellExplore(path+file);
						info_if_error(ret, file, menuitem.lastChild.data);
					  },
					  'term': function(t,menuitem) {
					    get_file_path(t);
						var ret = cef.plugin.term(path,file);
						info_if_error(ret, file, menuitem.lastChild.data);
					  },
					  'copypath': function(t,menuitem) {
					    get_file_path(t);
						var ret = cef.plugin.copyPath(path+file);
						info_or_error(ret, path+file, menuitem.lastChild.data);
					  },
					  'copy': function(t,menuitem) {
						copy_file(t);
					  },
					  'cut': function(t,menuitem) {
						cut_file(t);
					  },
					  'delete': function(t,menuitem) {
						delete_file(t);
					  },
					  'prop': function(t,menuitem) {
					    get_file_path(t);
						var ret = cef.plugin.shell2(path+file,"properties");
						info_if_error(ret, file, menuitem.lastChild.data);
					  }
					}
				  }

var context_menu_obj3 = {
				  menuStyle: {
					width : "150px"
				  },
				  itemStyle: {
				  },
				  itemHoverStyle: {
				  },
				  bindings: {
					  'default': function(t,menuitem) {
						var fs = grid_selectd_files();
						var ret = cef.plugin.batchOpen(fs);
						info_or_error(ret, fs, menuitem.lastChild.data);
					  },
					  'copy': function(t,menuitem) {
						var fs = grid_selectd_files();
						var ret = cef.plugin.batchCopy(fs);
						info_or_error(ret, fs, menuitem.lastChild.data);
					  },
					  'cut': function(t,menuitem) {
						var fs = grid_selectd_files();
						var ret = cef.plugin.batchCut(fs);
						info_or_error(ret, fs, menuitem.lastChild.data);
					  },
					  'delete': function(t,menuitem) {
						var fs = grid_selectd_files();
						if(true || window.confirm("您确定要删除 \n"+grid_selectd_filenames()+"这些文件吗?")){
							var ret = cef.plugin.batchDelete(fs);
							refresh();
							info_or_error(ret, fs, menuitem.lastChild.data);
						}
					  }
					}
				  }