$(function () {

	$.getJSON( "json/china.json" ).done(function ( response ) {
		var $clickCallback = $( "#click-callback" );
		jsMap.config( "#map-0", response, {
			areaName: {
				show: true
			},
			clickCallback: function ( id, name ) {
				const xhr = new XMLHttpRequest();
				const url = 'query';
				const data = {
					"type" : "queryMap",
					"provinceId": id,
					"provinceName": name
				};
				xhr.open('POST', url);
				xhr.setRequestHeader('Content-Type', 'application/json;charset=UTF-8');
				xhr.send(JSON.stringify(data));
				xhr.onload = function() {
				if (xhr.status === 200) {
					var json = JSON.parse(xhr.response);
					console.log(json.data)
					let p;
					let msg = "";
					for(p in json.data){
						msg = msg + "<p>" + json.data[p].name + ", " + json.data[p].cityName + ", "+ json.data[p].describe + "</p>"
					}
					document.getElementById("show").innerHTML = msg;
				} else {
					console.log('Request failed.  Returned status of ' + xhr.status);
					document.getElementById("show").innerHTML = 'Request failed.  Returned status of ' + xhr.status;
				}
				};
			}
		});
/*
		jsMap.config( "#map-01", response );

		jsMap.config( "#map-02", response, {
			areaName: {
				show: true
			}
		});

		jsMap.config( "#map-03", response, {
			multiple: true
		});
		$( "#get-multiple-1" ).on("click", function () {
			console.log( jsMap.multipleValue( "#map-03" ) );
		})
		$( "#get-multiple-2" ).on("click", function () {
			console.log( jsMap.multipleValue( "#map-03" , { type: "object" } ) );
		})

		jsMap.config( "#map-04", response, {
			stroke: {
				width: 2,
				color: "#000"
			}
		});

		jsMap.config( "#map-05", response, {
			fill: {
                basicColor: "#259200",
                hoverColor: "#57cb00",
                clickColor: "#2e6f18"
            }
		});

		jsMap.config( "#map-06", response, {
			fill: {
                basicColor: {
                    heilongjiang: "#ff5900",
                    jilin: "#19bb00",
                    liaoning: "#6800ff"
                },
                hoverColor: {
                    heilongjiang: "#ff8c4e",
                    jilin: "#1fe000",
                    liaoning: "#954dff"
                },
                clickColor: {
                    heilongjiang: "#c94600",
                    jilin: "#159a00",
                    liaoning: "#5200c9"
                }
            }
		});

		jsMap.config( "#map-07", response, {
			disabled: {
				name: [ "heilongjiang", "jilin", "liaoning" ]
			}
		});

		jsMap.config( "#map-08", response, {
			disabled: {
				name: [ "heilongjiang", "jilin", "liaoning" ],
				except: true
			}
		});

		jsMap.config( "#map-09", response, {
			tip: function ( id, name ) {
                return '<div style="background:#eee;padding:15px;"><p>id: ' + id + '</p><p>name: ' + name + '</p></div>';
            }
		});

		var $hoverCallback = $( "#hover-callback" );
		jsMap.config( "#map-10", response, {
			hoverCallback: function ( id, name ) {
				$hoverCallback.text( id + " --- " + name );
			}
		});

		var $clickCallback = $( "#click-callback" );
		jsMap.config( "#map-11", response, {
			clickCallback: function ( id, name ) {
				$clickCallback.text( id + " --- " + name );
			}
		});
		*/

	})

})