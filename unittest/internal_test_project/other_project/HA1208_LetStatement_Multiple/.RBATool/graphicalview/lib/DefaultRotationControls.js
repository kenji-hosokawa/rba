THREE.DefaultRotationControls = function ( _object, _domElement ) {

	var _mouse = new THREE.Vector2();
	var _offset = new THREE.Vector3();
    var _rotating = false;

    var _previousMousePosition = {
        x: 0,
        y: 0
    };

	var scope = this;

	function activate() {

		_domElement.addEventListener( 'mousemove', onDocumentMouseMove, false );
		_domElement.addEventListener( 'mousedown', onDocumentMouseDown, false );
		_domElement.addEventListener( 'mouseup', onDocumentMouseCancel, false );
		_domElement.addEventListener( 'mouseleave', onDocumentMouseCancel, false );
		_domElement.addEventListener( 'touchmove', onDocumentTouchMove, false );
		_domElement.addEventListener( 'touchstart', onDocumentTouchStart, false );
		_domElement.addEventListener( 'touchend', onDocumentTouchEnd, false );

	}

	function deactivate() {

		_domElement.removeEventListener( 'mousemove', onDocumentMouseMove, false );
		_domElement.removeEventListener( 'mousedown', onDocumentMouseDown, false );
		_domElement.removeEventListener( 'mouseup', onDocumentMouseCancel, false );
		_domElement.removeEventListener( 'mouseleave', onDocumentMouseCancel, false );
		_domElement.removeEventListener( 'touchmove', onDocumentTouchMove, false );
		_domElement.removeEventListener( 'touchstart', onDocumentTouchStart, false );
		_domElement.removeEventListener( 'touchend', onDocumentTouchEnd, false );

	}

	function dispose() {

		deactivate();

	}

	function onDocumentMouseMove( event ) {

		event.preventDefault();

		if ( _rotating && scope.enabled && _object ) {

            var deltaMove = {
                x: event.offsetX - _previousMousePosition.x,
                y: event.offsetY - _previousMousePosition.y
            };

            var deltaRotationQuaternion = new THREE.Quaternion()
                .setFromEuler(new THREE.Euler(
                    0,
                    toRadian(deltaMove.x * 1),
                    0,
                    'XYZ'
                ));

            _object.quaternion.multiplyQuaternions(deltaRotationQuaternion, _object.quaternion);

            _previousMousePosition = {
                x: event.offsetX,
                y: event.offsetY
            }

			scope.dispatchEvent( { type: 'rotate', object: _object } );

			return;
        }

		var rect = _domElement.getBoundingClientRect();

		_mouse.x = ( ( event.clientX - rect.left ) / rect.width ) * 2 - 1;
		_mouse.y = - ( ( event.clientY - rect.top ) / rect.height ) * 2 + 1;

	}

	function onDocumentMouseDown( event ) {

        event.preventDefault();

        _previousMousePosition = {
            x: event.offsetX,
            y: event.offsetY
        }

        _rotating = true;
		scope.dispatchEvent( { type: 'rotatestart', object: _object } );

	}

	function onDocumentMouseCancel( event ) {

		event.preventDefault();

		if ( _rotating && _object ) {

			scope.dispatchEvent( { type: 'rotateend', object: _object } );

			_rotating = false;

		}

		_domElement.style.cursor = 'auto';

	}

	function onDocumentTouchMove( event ) {

		event.preventDefault();
		event = event.changedTouches[ 0 ];

		var rect = _domElement.getBoundingClientRect();

		_mouse.x = ( ( event.clientX - rect.left ) / rect.width ) * 2 - 1;
		_mouse.y = - ( ( event.clientY - rect.top ) / rect.height ) * 2 + 1;

        if ( _rotating && scope.enabled && _object ) {

            var deltaMove = {
                x: event.offsetX - _previousMousePosition.x,
                y: event.offsetY - _previousMousePosition.y
            };

            var deltaRotationQuaternion = new THREE.Quaternion()
                .setFromEuler(new THREE.Euler(
                    0,
                    toRadian(deltaMove.x * 1),
                    0,
                    'XYZ'
                ));

            _object.quaternion.multiplyQuaternions(deltaRotationQuaternion, _object.quaternion);

            _previousMousePosition = {
                x: event.offsetX,
                y: event.offsetY
            }

			scope.dispatchEvent( { type: 'rotate', object: _object } );

			return;
		}

	}

	function onDocumentTouchStart( event ) {

		event.preventDefault();
		event = event.changedTouches[ 0 ];

		var rect = _domElement.getBoundingClientRect();

		_mouse.x = ( ( event.clientX - rect.left ) / rect.width ) * 2 - 1;
		_mouse.y = - ( ( event.clientY - rect.top ) / rect.height ) * 2 + 1;

		scope.dispatchEvent( { type: 'rotatestart', object: _object } );

	}

	function onDocumentTouchEnd( event ) {

		event.preventDefault();

		if ( _rotating ) {

			scope.dispatchEvent( { type: 'rotateend', object: _object } );

			_rotating = false;

		}

		_domElement.style.cursor = 'auto';

	}

	activate();

	// API

	this.enabled = true;

	this.activate = activate;
	this.deactivate = deactivate;
	this.dispose = dispose;

	// Backward compatibility

	this.setObjects = function () {

		console.error( 'THREE.DefaultRotationControls: setObjects() has been removed.' );

	};

	this.on = function ( type, listener ) {

		console.warn( 'THREE.DefaultRotationControls: on() has been deprecated. Use addEventListener() instead.' );
		scope.addEventListener( type, listener );

	};

	this.off = function ( type, listener ) {

		console.warn( 'THREE.SimpleRotationControls: off() has been deprecated. Use removeEventListener() instead.' );
		scope.removeEventListener( type, listener );

	};

	this.notify = function ( type ) {

		console.error( 'THREE.DefaultRotationControls: notify() has been deprecated. Use dispatchEvent() instead.' );
		scope.dispatchEvent( { type: type } );

	};

};

function toRadian(angle) {
    return angle * (Math.PI / 180);
}

function toDegree(angle) {
    return angle * (180 / Math.PI);
}

THREE.DefaultRotationControls.prototype = Object.create( THREE.EventDispatcher.prototype );
THREE.DefaultRotationControls.prototype.constructor = THREE.DefaultRotationControls;
