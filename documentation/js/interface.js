var formatted = true;

$(document).ready(function () {
	$("pre.prettyprint").each(function () {
		var clone = $(this).clone();
		clone.removeClass("prettyprint");
		clone.addClass("unformatted");
		$(this).before(clone);
		clone.hide();
	});
	
	prettyPrint();
	
	$("#clearFormatting").click(function () {
		if (formatted) {
			$(this).text("Show Code Formatting");
			$(".prettyprint").hide();
			$(".unformatted").show();
		} else { 
			$(this).text("Clear Code Formatting");
			$(".prettyprint").show();
			$(".unformatted").hide();
		}
		formatted = !formatted;
		return false;
	});
});




