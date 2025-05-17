import cv2
import mediapipe as mp
import math

# Output file path (update to absolute path if needed)
OUTPUT_FILE = "tilt_angle.txt"

# Setup mediapipe face mesh
mp_face_mesh = mp.solutions.face_mesh
face_mesh = mp_face_mesh.FaceMesh(static_image_mode=False, max_num_faces=1)

cap = cv2.VideoCapture(0)

def write_direction(direction):
    with open(OUTPUT_FILE, "w") as f:
        f.write(direction)

def get_angle(p1, p2):
    """Returns the angle between two points in degrees"""
    dx, dy = p2[0] - p1[0], p2[1] - p1[1]
    return math.degrees(math.atan2(dy, dx))

while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        break

    h, w, _ = frame.shape
    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    result = face_mesh.process(rgb_frame)

    direction = "CENTER"

    if result.multi_face_landmarks:
        for landmarks in result.multi_face_landmarks:
            # Nose tip and eyes landmarks
            nose_tip = landmarks.landmark[1]
            left_eye = landmarks.landmark[33]
            right_eye = landmarks.landmark[263]
            forehead = landmarks.landmark[10]
            chin = landmarks.landmark[152]

            nose = (int(nose_tip.x * w), int(nose_tip.y * h))
            left = (int(left_eye.x * w), int(left_eye.y * h))
            right = (int(right_eye.x * w), int(right_eye.y * h))
            top = (int(forehead.x * w), int(forehead.y * h))
            bottom = (int(chin.x * w), int(chin.y * h))

            # Horizontal head tilt (left/right)
            eye_angle = get_angle(left, right)
            # Vertical head tilt (up/down)
            vert_angle = get_angle(top, bottom)

            # Define thresholds (tweak for sensitivity)
            if eye_angle > 10:
                direction = "LEFT"
            elif eye_angle < -10:
                direction = "RIGHT"
            elif vert_angle > 15:
                direction = "DOWN"
            elif vert_angle < -15:
                direction = "UP"
            else:
                direction = "CENTER"

            write_direction(direction)

            # Debug display
            cv2.putText(frame, f"Direction: {direction}", (30, 30),
                        cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

    cv2.imshow("Head Tilt Tracker", frame)

    if cv2.waitKey(1) & 0xFF == 27:  # ESC to quit
        break

cap.release()
cv2.destroyAllWindows()
