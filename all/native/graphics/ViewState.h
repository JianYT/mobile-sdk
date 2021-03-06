/*
 * Copyright (c) 2016 CartoDB. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://cartodb.com/terms/
 */

#ifndef _CARTO_VIEWSTATE_H_
#define _CARTO_VIEWSTATE_H_

#include "core/MapRange.h"
#include "components/Options.h"

#include <cglib/vec.h>
#include <cglib/mat.h>
#include <cglib/frustum3.h>

namespace carto {
    class ProjectionSurface;
        
    /**
     * A class containing various view parameters for a view state.
     */
    class ViewState {
    public:
        /** 
         * A container class for a partial rotation matrix for a view state.
         */
        struct RotationState {
            cglib::vec3<float> xAxis;
            cglib::vec3<float> yAxis;
        };
    
        /**
         * Constructs an uninitialized ViewState object.
         */
        ViewState();
        virtual ~ViewState();
    
        /**
         * Returns the camera position.
         * @return The camera position.
         */
        const cglib::vec3<double>& getCameraPos() const;
        /**
         * Sets the camera position. Changing the camera position doesn't 
         * automatically update the view. To update the view cameraChanged() must be called.
         * @param cameraPos The new camera position.
         */
        void setCameraPos(const cglib::vec3<double>& cameraPos);

        /**
         * Returns the focus position.
         * @return The focus position.
         */
        const cglib::vec3<double>& getFocusPos() const;
        /**
         * Sets the focus position. Changing the focus position doesn't
         * automatically update the view. To update the view cameraChanged() must be called.
         * @param focusPos The new focus position.
         */
        void setFocusPos(const cglib::vec3<double>& focusPos);

        /**
         * Returns the up direction vector.
         * @return The up direction vector.
         */
        const cglib::vec3<double>& getUpVec() const;
        /**
         * Sets the up direction vector. Changing the up direction vector doesn't
         * automatically update the view. To update the view cameraChanged() must be called.
         * @param upVec The new up direction vector.
         */
        void setUpVec(const cglib::vec3<double>& upVec);
    
        /**
         * Returns the camera tilt angle.
         * @return The camera tilt angle in degrees.
         */
        float getTilt() const;
        /**
         * Sets the camera tilt angle. Changing the tilt angle doesn't
         * automatically update the view. To update the view cameraChanged() must be called.
         * @param tilt The new camera tilt angle in degrees.
         */
        void setTilt(float tilt);

        /**
         * Returns the camera zoom level.
         * @return The camera zoom level.
         */
        float getZoom() const;
        /**
         * Sets the camera zoom level. Changing the zoom level doesn't
         * automatically update the view. To update the view cameraChanged() must be called.
         * @param zoom The new camera zoom level.
         */
        void setZoom(float zoom);

        /**
         * Returns the state of the camera changed flag.
         * @return True if camera has changed since the last frame.
         */
        bool isCameraChanged() const;
        /**
         * Sets the state of the camera changed flag to true. This means the view will get
         * updated at the beginning of the next frame.
         */
        void cameraChanged();
        
        /**
         * Returns the camera rotation angle.
         * @return The camera rotation angle in degrees.
         */
        float getRotation() const;

        /**
         * Returns the number 2 lifted to the power of the zoom level: pow(2, zoom level).
         * @return pow(2, zoom level).
         */
        float get2PowZoom() const;
        /**
         * Returns the distance between the focus and the camera position, when the zoom level is set to 0.
         * This parameter depends on the screen size, DPI, tile draw size and field of view settings.
         * @return The distance between focus to camera position, when zoom level = 0.
         */
        float getZoom0Distance() const;

        /**
         * Returns the adjusted minimum zoom.
         * If restricted panning is used, then this value can be greater than the minimum zoom specified
         * via Options.
         * @return The minimum zoom of the map view.
         */
        float getMinZoom() const;
        
        /**
         * Get normalized resolution of the view. This is an internal parameter used by vector tile renderer.
         * @return The screen resolution of the view.
         */
        float getNormalizedResolution() const;
    
        /**
         * Returns the width of the map screen.
         * @return The map screen width.
         */
        int getWidth() const;
        /**
         * Returns the height of the map screen.
         * @return The map screen height.
         */
        int getHeight() const;
        /**
         * Returns the width of the map screen divided by 2.
         * @return The map screen width divided by 2.
         */
        float getHalfWidth() const;
        /**
         * Returns the height of the map screen divided by 2.
         * @return The map screen height divided by 2.
         */
        float getHalfHeight() const;
        /**
         * Returns the aspect ratio of the map screen. Equal to width / height.
         * @return The aspect ratio of the map screen.
         */
        float getAspectRatio() const;

        /**
         * Returns the near plane distance.
         * @return The new plane distance.
         */
        float getNear() const;
        /**
         * Returns the far plane distance.
         * @return The far plane distance.
         */
        float getFar() const;
    
        /**
         * Returns the vertical field of view angle.
         * @return The vertical field of view angle in degrees.
         */
        int getFOVY() const;
        /**
         * Returns the vertical field of view angle, divided by 2.
         * @return The vertical field of view angle in degrees, divided by 2.
         */
        float getHalfFOVY() const;
        /**
         * Returns the tangent of the half vertical FOV angle.
         * @return The tangent of the half vertical FOV angle.
         */
        double getTanHalfFOVY() const;
        /**
         * Returns the cosine of the half vertical FOV angle.
         * @return The cosine of the half vertical FOV angle.
         */
        double getCosHalfFOVY() const;
        /**
         * Returns the tangent of the half horizontal FOV angle.
         * @return The tangent of the half horizontal FOV angle.
         */
        double getTanHalfFOVX() const;
        /**
         * Returns the cosine of the half horizontal FOV angle multiplied 
         * by the cosine of the half vertical FOV angle.
         * @return The cosine of the half horizontal FOV angle multiplied
         * by the cosine of the half vertical FOV angle.
         */
        double getCosHalfFOVXY() const;
        
        /**
         * Returns a value that is used for converting display independent pixels (dp) to pixels (px).
         * This values depends on the screen density.
         * @return The dp to px value.
         */
        float getDPToPX() const;
        /**
         * Returns the dots per inch parameter of the screen.
         * @return The screen DPI parameter.
         */
        float getDPI() const;
    
        /**
         * Returns the conversion ratio between internal map units and screen pixels. This parameter is dependent
         * on the zoom level and other screen parameters.
         * @return The conversion ratio between internal map units and screen pixels.
         */
        float getUnitToPXCoef() const;
        /**
         * Returns the conversion ratio between internal map units and screen density independent pixels (DP or DIP). 
         * This parameter is dependent on the zoom level, DPI and other screen parameters.
         * @return The conversion ratio between internal map units and screen density independent pixels.
         */
        float getUnitToDPCoef() const;
        /**
         * Returns the partial rotation matrix representing this view state.
         * @return The partial rotation matrix representing this view state.
         */
        const RotationState& getRotationState() const;
    
        /**
         * Returns the projection surface.
         * @return The projection surface.
         */
        std::shared_ptr<ProjectionSurface> getProjectionSurface() const;
    
        /**
         * Returns the projection matrix.
         * @return The projection matrix.
         */
        const cglib::mat4x4<double>& getProjectionMat() const;
        /**
         * Returns the modelview matrix.
         * @return The modelview matrix.
         */
        const cglib::mat4x4<double>& getModelviewMat() const;
        /**
         * Returns the modelview-projection matrix. This is equivalent to the the projeciton matrix multiplied with the
         * modelview matrix.
         * @return The modelview-projection matrix.
         */
        const cglib::mat4x4<double>& getModelviewProjectionMat() const;
        /**
         * Returns the relative-to-eye modelview matrix. This equivalent to the modelview matrix with the first
         * three elements of the last column set to 0.
         * @return The relative-to-eye modelview matrix.
         */
        const cglib::mat4x4<float>& getRTEModelviewMat() const;
        /**
         * Returns the relative-to-eye modelview-projection matrix. This is equivalent to the projection matrix 
         * multiplied with the relative-to-eye modelview matrix.
         * @return The relative-to-eye modelview-projection matrix.
         */
        const cglib::mat4x4<float>& getRTEModelviewProjectionMat() const;
        /**
         * Returns the relative-to-eye modelview-projection matrix with pushed back far plane.
         * @return The relative-to-eye modelview-projection matrix.
         */
        const cglib::mat4x4<float>& getRTESkyProjectionMat() const;

        /**
         * Returns the view frustum.
         * @return The view frustum.
         */
        const cglib::frustum3<double>& getFrustum() const;
    
        /**
         * Returns the screen width.
         * @return The current screen width.
         */
        int getScreenWidth() const;
        /**
         * Returns the screen height.
         * @return The current screen height.
         */
        int getScreenHeight() const;
        /**
         * Sets the screen size. The view will be updated at the beginning of the next frame.
         * @param width The new width of the screen.
         * @param height The new height of the screen.
         */
        void setScreenSize(int width, int height);

        /**
         * Clamps the zoom level if restricted panning is used.
         * @param options The options object to use for clamping.
         */
        void clampZoom(const Options& options);
        /**
         * Clamps the focus point if restricted panning is used.
         * @param options The options object to use for clamping.
         */
        void clampFocusPos(const Options& options);

        /**
         * Returns the normal vector at focus point.
         * @return The normal vector at focus point.
         */
        cglib::vec3<float> getFocusPosNormal() const;

        /**
         * Returns true if sky is visible.
         * @return True if sky is visible.
         */
        bool isSkyVisible() const;

        /**
         * Updates the view when the screen size, view state or some other view options have changed. This is automatically
         * called at the beginning of every frame.
         * @param options The state of options.
         */
        void calculateViewState(const Options& options);
    
        /**
         * Projects a screen position into the projection surface (world) using the current view state.
         * @param screenPos The screen position.
         * @param height The height in world space.
         * @param options The options object.
         * @return The screen position projected into the map plane, in internal coordinates. If screen position does not hit projection surface, NaNs are returned.
         */
        cglib::vec3<double> screenToWorld(const cglib::vec2<float>& screenPos, double height, std::shared_ptr<Options> options = std::shared_ptr<Options>()) const;
        /**
         * Projects a world position onto the screen using the current view state.
         * @param worldPos The world position.
         * @param options The options object.
         * @return The world position projected onto the screen, in pixel coordinates.
         */
        cglib::vec2<float> worldToScreen(const cglib::vec3<double>& worldPos, std::shared_ptr<Options> options = std::shared_ptr<Options>()) const;
        /**
         * Estimates a pixel measure in internal coordinate scale. The estimate is based on focus point.
         * @return The pixel measure in internal coordinate scale.
         */
        float estimateWorldPixelMeasure() const;
    
        /**
         * Returns the horizontal offset direction, caused by seamless panning horizontally over the map borders.
         * @return The horizontal offset direction.
         */
        int getHorizontalLayerOffsetDir() const;
        /**
         * Sets the horizontal offset direction. This method is called when seamless panning is enabled and
         * the user pans horizontally over the map borders.
         * @param horizontalLayerOffsetDir The horizontal offset direction, -1 for left, 0 for none, 1 for right.
         */
        void setHorizontalLayerOffsetDir(int horizontalLayerOffsetDir);
    
    private:
        void calculateViewDistances(const Options& options, float& near, float& far, bool& skyVisible) const;
        float calculateMinZoom(const Options& options) const;
        MapPos calculateMapBoundsCenter(const Options& options, const MapBounds& mapBounds) const;
   
        cglib::mat4x4<double> calculatePerspMat(float halfFOVY, float near, float far, const Options& options) const;
        cglib::mat4x4<double> calculateLookatMat() const;
        cglib::mat4x4<double> calculateModelViewMat(const Options& options) const;

        cglib::vec3<double> _cameraPos;
        cglib::vec3<double> _focusPos;
        cglib::vec3<double> _upVec;
        bool _cameraChanged;
    
        float _rotation;
        float _tilt;
        float _zoom;
        float _2PowZoom;
        float _zoom0Distance;
        float _minZoom;
        bool _ignoreMinZoom;
        MapRange _zoomRange;
        bool _restrictedPanning;
        float _normalizedResolution;
    
        int _width;
        int _height;
        float _halfWidth;
        float _halfHeight;
        float _aspectRatio;
        bool _screenSizeChanged;
    
        float _near;
        float _far;
        bool _skyVisible;
    
        int _fovY;
        float _halfFOVY;
        double _tanHalfFOVY;
        double _cosHalfFOVY;
        double _tanHalfFOVX;
        double _cosHalfFOVXY;
    
        int _tileDrawSize;
        
        float _dpToPX;
        float _dpi;
    
        float _unitToPXCoef;
        float _unitToDPCoef;
        RotationState _rotationState;
    
        std::shared_ptr<ProjectionSurface> _projectionSurface;

        cglib::mat4x4<double> _projectionMat;
        cglib::mat4x4<double> _modelviewMat;
        cglib::mat4x4<double> _modelviewProjectionMat;
        cglib::mat4x4<float> _rteModelviewMat;
        cglib::mat4x4<float> _rteModelviewProjectionMat;
        cglib::mat4x4<float> _rteSkyProjectionMat;

        cglib::frustum3<double> _frustum;
    
        int _horizontalLayerOffsetDir;
    };
    
}

#endif
