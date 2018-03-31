var express = require('express');
var router = express.Router();

var kengPool = {
	"67tw2f35Hye9N7sx": {
		name: "KX F3-C1",
		state: [0,0,0,0]
	}
}
/* GET users listing. */
router.get('/update/:token/:value', function(request, response, next) {
	var params = request.params||{};
	var data = extractData(params)
	response.json({
		token: params.token,
		value: params.value,
		data: data
	});
});

module.exports = router;


function extractData(params){
	if(params && params.token && params.value*1){
		var keng = kengPool[params.token];
		var value = params.value.split('').map(function(a, i){
			if(i>0){
				if(a==="1"){
					return 1;
				}else{
					return 0;
				}
			}
			return "";
		}).reverse();
		if(keng && value.length){
			value.pop();
			keng.state = value;
			return keng;			
		}
	}
	return false;
}